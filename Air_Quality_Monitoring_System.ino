String key; //ตัวแปรเก็บค่าที่คอมพิวเตอร์ส่งมา
int runs = 0;
int i, j = -1, o = -1;
float data[4][4] = {};
float sigmaX[4] = {}, sigmaY, sigmaXY[4] = {}, sigmaX2[4] = {}, b[4] = {}, a[4] = {}, Xbar[4] = {}, Ybar;
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

void setup()
{
  Serial.begin(9600);
  while (!Serial);   // time to get serial running
  Serial.println(F("BME280 test"));
  unsigned status;
  // default settings
  //status = bme.begin();
  // You can also pass in a Wire library object like &Wire2
   status = bme.begin(0x76);
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
void loop()
{
  if (runs == 0) {
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
  if (Serial.available() > 0) { //ถ้าคอมพิวเตอร์ส่งข้อมูลมาใหจะทำใน if นี้
    key = Serial.readString(); //นำค่าที่คอมพิวเตอร์ส่งมาเก็บในตัวแปร key
    Serial.print("key : ");
    Serial.println(key); //Arduino ส่งค่าในตัวแปร key เข้าคอมพิวเตอร์ Serial Monitor
    if (key == "300") {
      j = 3;
    } else if (key == "200") {
      j = 2;
    } else if (key == "100") {
      j = 1;
    } else if (key == "0") {
      j = 0;
    } else if (key == "G") {
      for (i = 0; i <= 3; i++) {
        Serial.println("");
        for (j = 0; j <= 3; j++) {
          Serial.print(data[i][j]);
          Serial.print(",");
        }
      }
      Serial.println("");
      runs = 1;
      regression();
    } else if (key == "C") {
      i = 0;
      Serial.println("");
      Serial.print("Sen0 = ");
      Serial.print((analogRead(A0)*b[i]) + a[i]);
      Serial.println(" ppm");
      i++;
      Serial.print("Sen1 = ");
      Serial.print((analogRead(A1)*b[i]) + a[i]);
      Serial.println(" ppm");
      i++;
      Serial.print("Sen2 = ");
      Serial.print((analogRead(A2)*b[i]) + a[i]);
      Serial.println(" ppm");
      i++;
      Serial.print("Sen3 = ");
      Serial.print((analogRead(A3)*b[i]) + a[i]);
      Serial.println(" ppm");
      Serial.print("Temp = ");
      Serial.print(bme.readTemperature());
      Serial.print("  Hum = ");
      Serial.println(bme.readHumidity());
    }
    if (j != o) {
      Serial.println("");
      data[0][j] = analogRead(A0);
      Serial.print(analogRead(A0));
      Serial.print(",");
      data[1][j] = analogRead(A1);
      Serial.print(analogRead(A1));
      Serial.print(",");
      data[2][j] = analogRead(A2);
      Serial.print(analogRead(A2));
      Serial.print(",");
      data[3][j] = analogRead(A3);
      Serial.println(analogRead(A3));
      o = j;
    }
  }
}
void regression() {
  sigmaY = 0 + 100 + 200 + 300;
  //Serial.println(sigmaY);
  Ybar = sigmaY / 4;
  //Serial.println(Ybar);
  for (i = 0; i <= 3; i++) {
    sigmaX[i] = (data[i][0] + data[i][1] + data[i][2] + data[i][3]);
    //Serial.println(sigmaX[i]);
    Xbar[i] = sigmaX[i] / 4;
    //Serial.println(Xbar[i]);
    sigmaXY[i] = (data[i][0] * 0 + data[i][1] * 100 + data[i][2] * 200 + data[i][3] * 300);
    //Serial.println(sigmaXY[i]);
    sigmaX2[i] = ((data[i][0] * data[i][0]) + (data[i][1] * data[i][1]) + (data[i][2] * data[i][2]) + (data[i][3] * data[i][3]));
    //Serial.println(sigmaX2[i]);
    b[i] = ((4 * sigmaXY[i]) - (sigmaX[i] * sigmaY)) / ((4 * sigmaX2[i]) - (sigmaX[i] * sigmaX[i]));
    a[i] = Ybar - (b[i] * Xbar[i]);
    Serial.print("Equation : ");
    Serial.print(b[i]);
    Serial.print("x+");
    Serial.print(a[i]);
    Serial.print("  Temp = ");
    Serial.print(bme.readTemperature());
    Serial.print("  Hum = ");
    Serial.println(bme.readHumidity());
  }
}
