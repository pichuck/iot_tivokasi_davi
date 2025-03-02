#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C  // Alamat I2C dari SSD1306

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 27     
#define DHTTYPE DHT22   

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx + OLED Test"));

  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 initialization failed!"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 10);
  display.println("DHT22 Sensor Ready!");
  display.display();
  delay(2000);
}

void loop() {
  delay(2000); // Sensor DHT22 memiliki delay minimal 2 detik

  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Celsius
  float f = dht.readTemperature(true); // Fahrenheit

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    display.clearDisplay();
    display.setCursor(10, 10);
    display.println("Sensor Error!");
    display.display();
    return;
  }

  Serial.print(F("Humidity: ")); Serial.print(h);
  Serial.print(F("%  Temperature: ")); Serial.print(t);
  Serial.print(F("°C ")); Serial.print(f);
  Serial.println(F("°F"));

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  display.setCursor(10, 10);
  display.print("Temp: ");
  display.print(t);
  display.print(" C");

  display.setCursor(10, 30);
  display.print("Humidity: ");
  display.print(h);
  display.print(" %");

  display.display();
}
