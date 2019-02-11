//
//    FILE: 4x7segmentI2C.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.0.1
// PURPOSE: demo
//     URL: http://www.adafruit.com/products/1002
// HISTORY:

#include <Wire.h>
#include "HT16K33.h"

HT16K33 seg;

uint32_t start;
uint32_t stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  seg.begin(0x70);
  Wire.setClock(100000);

  seg.displayOn();
  Serial.println("displayTest()");
  seg.displayTest(100);
  seg.displayOff();
  delay(1000);
  seg.displayOn();
}

void loop()
{
  Serial.println("Int");
  seg.displayInt(9999);
  delay(1000);

  Serial.println("Hex");
  seg.displayHex(0xABCF);
  delay(1000);

  Serial.println("dim()");
  for (int i = 0; i < 16; i++)
  {
    seg.brightness(i);
    delay(500);
  }
  for (int i = 15; i > 0; i--)
  {
    seg.brightness(i);
    delay(500);
  }
  seg.brightness(2);

  Serial.println("displayClear()");
  seg.displayClear();
  delay(1000);

  Serial.println("displayTime()");
  seg.displayTime(13, 25);
  for (int i = 50; i < 60; i++)
  {
    seg.displayTime(13, i);
    delay(500);
    seg.displayColon(true);
    delay(500);
  }

  Serial.println("float");
  seg.displayClear();
  delay(500);
  seg.displayFloat(3.14159265);
  delay(500);
  seg.displayFloat(99999);
  delay(500);
  seg.displayFloat(9999);
  delay(500);
  seg.displayFloat(31.4159265);
  delay(500);
  seg.displayFloat(314.159265);
  delay(500);
  seg.displayFloat(3141.59265);
  delay(500);
  seg.displayFloat(0.314159265);
  delay(500);
  seg.displayFloat(0.0314159265);
  delay(500);
  seg.displayFloat(0.00314159265);
  delay(500);
  seg.displayFloat(0.000314159265);
  delay(500);


  Serial.println("Voltmeter");
  for (int i = 0; i < 100; i++)
  {
    float voltage = analogRead(A0) * 5.0 / 1023;
    seg.displayFloat(voltage);
    delay(100);
  }

  Serial.println("blink()");
  for (uint8_t i = 0; i < 3; i++)
  {
    seg.blink(i);
    delay(4000);
  }
  seg.blink(0);

  Serial.print("INT TEST:\t");
  start = millis();
  for (uint16_t counter = 0; counter < 9999; counter++)
  {
    seg.displayInt(counter);
  }
  stop = millis();
  Serial.println(stop - start);


  Serial.print("HEX TEST:\t");
  start = millis();
  for (uint16_t counter = 0; counter < 0xFFFF; counter++)
  {
    seg.displayHex(counter);
  }
  stop = millis();
  Serial.println(stop - start);
}