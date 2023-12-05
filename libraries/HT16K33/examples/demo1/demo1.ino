//
//    FILE: demo1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: http://www.adafruit.com/products/1002
//     URL: https://github.com/RobTillaart/HT16K33


#include "HT16K33.h"

HT16K33 seg(0x70);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HT16K33_LIB_VERSION: ");
  Serial.println(HT16K33_LIB_VERSION);

  Wire.begin();
  Wire.setClock(100000);
  seg.begin();

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
    seg.displayHex(0xABC0 + i);
    seg.setBrightness(i);
    delay(500);
  }
  for (int i = 15; i >= 0; i--)
  {
    seg.displayHex(0xABC0 + i);
    seg.setBrightness(i);
    delay(500);
  }
  delay(1000);
  seg.setBrightness(2);

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

  Serial.println("displayDate()");
  uint8_t dpm[12] = { 31, 28, 31, 30,   31, 30, 31, 31,   30, 32, 30, 31 };
  for (uint8_t mo = 0; mo < 12; mo++)
  {
    for (uint8_t da = 1; da <= dpm[mo]; da++)
    {
      seg.displayDate(mo + 1, da);
      delay(200);
    }
  }

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

  Serial.println("setBlink()");
  for (uint8_t i = 0; i < 3; i++)
  {
    seg.displayHex(0xABC0 + i);
    seg.setBlink(i);
    delay(4000);
  }
  seg.setBlink(0);

  Serial.print("INT TEST:\t");
  start = millis();
  for (int16_t counter = -999; counter < 9999; counter++)
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

  //  Serial.print("SUPRESS ZERO TEST:\t");
  //  for (uint8_t nlz = 0; nlz < 5; nlz++)
  //  {
  //    Serial.print(nlz);
  //    seg.suppressLeadingZeroPlaces(nlz);
  //    seg.displayInt(0);
  //    delay(1000);
  //  }
  //  seg.suppressLeadingZeroPlaces(0);

  Serial.print("SET DIGITS TEST:\t");
  for (uint8_t dig = 0; dig < 5; dig++)
  {
    Serial.print(dig);
    seg.setDigits(dig);
    seg.displayInt(0);
    delay(1000);
  }
  seg.setDigits(1);

}


//  -- END OF FILE --

