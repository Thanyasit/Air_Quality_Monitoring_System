unsigned long   Sen1 = 500;
unsigned long   Sen2 = 750;
unsigned long   Sen3 = 1000;
unsigned long   Sen4 = 1250;
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

void setup() {
  Serial.begin(9600);
  while (!Serial);   // time to get serial running
  Serial.println(F("BME280 test"));

  unsigned status;

  // default settings
  status = bme.begin();
  // You can also pass in a Wire library object like &Wire2
  // status = bme.begin(0x76, &Wire2)
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);

  }
  Serial.println("LABEL,DATATIME,Sen1,Sen2,Sen3,Sen4,Temp,Hum");
}
void loop() {
  if (millis() >= Sen1) {
    Serial.print("DATA,TIME");
    Serial.print(",");
    Serial.print(analogRead(A0));
    Serial.print(",");
    Sen1 = millis();
    Sen1 = Sen1 + 1000;
  } else if (millis() >= Sen2) {
    Serial.print(analogRead(A1));
    Serial.print(",");
    Sen2 = millis();
    Sen2 = Sen2 + 1000;
  } else if (millis() >= Sen3) {
    Serial.print(analogRead(A2));
    Serial.print(",");
    Sen3 = millis();
    Sen3 = Sen3 + 1000;
  } else if (millis() >= Sen4) {
    Serial.print(analogRead(A3));
    Serial.print(",");
    Serial.print(bme.readTemperature());
    Serial.print(",");
    Serial.println(bme.readHumidity());
    Sen4 = millis();
    Sen4 = Sen4 + 1000;
  }
}
