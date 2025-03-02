#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// Definisi pin untuk TFT ILI9341
#define TFT_CS   5
#define TFT_RST  4
#define TFT_DC   2
#define TFT_MOSI 23
#define TFT_SCK  18
#define TFT_MISO 19 // Tidak digunakan untuk output ke layar

// Inisialisasi layar TFT
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// Definisi pin untuk lampu lalu lintas
const int lampuMerah = 27;
const int lampuKuning = 26;
const int lampuHijau = 33; 

void setup() {
    Serial.begin(115200);
    Serial.println("ESP32 Traffic Light dengan TFT ILI9341");

    // Konfigurasi pin output untuk lampu lalu lintas
    pinMode(lampuMerah, OUTPUT);
    pinMode(lampuKuning, OUTPUT);
    pinMode(lampuHijau, OUTPUT);

    // Inisialisasi TFT
    tft.begin();
    tft.setRotation(0); // Sesuaikan orientasi layar jika perlu
    tft.fillScreen(ILI9341_BLACK); // Bersihkan layar awal
}

// Fungsi untuk menampilkan angka countdown dengan warna tertentu
void tampilkanCountdown(int waktu, uint16_t warna) {
    for (int i = waktu; i >= 0; i--) {
        tft.fillScreen(ILI9341_BLACK); // Bersihkan layar
        tft.setTextSize(5); // Ukuran angka besar
        tft.setTextColor(warna);
        
        // Posisi angka di tengah layar
        int xPos = (tft.width() - 30) / 2; // Menyesuaikan ukuran font
        int yPos = (tft.height() - 30) / 2;
        
        tft.setCursor(xPos, yPos);
        tft.print(i);
        Serial.println(String(i));
        delay(1000);
    }
}

void loop() {
    // Lampu merah (30 detik)
    digitalWrite(lampuMerah, HIGH);
    digitalWrite(lampuKuning, LOW);
    digitalWrite(lampuHijau, LOW);
    tampilkanCountdown(30, ILI9341_RED);

    // Lampu kuning (5 detik)
    digitalWrite(lampuMerah, LOW);
    digitalWrite(lampuKuning, HIGH);
    digitalWrite(lampuHijau, LOW);
    tampilkanCountdown(5, ILI9341_YELLOW);

    // Lampu hijau (20 detik)
    digitalWrite(lampuMerah, LOW);
    digitalWrite(lampuKuning, LOW);
    digitalWrite(lampuHijau, HIGH);
    tampilkanCountdown(20, ILI9341_GREEN);
}
