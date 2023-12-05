//
//    FILE: demo_displayInt.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: http://www.adafruit.com/products/1002
//     URL: https://github.com/RobTillaart/HT16K33


#include "HT16K33.h"

HT16K33 seg(0x70);


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
  seg.setBrightness(2);
  seg.displayClear();
  seg.setBlink(0);
}


void loop()
{
  Serial.print("INT TEST 0:\t");
  for (int16_t d = 4; d >= 0; d--)
  {
    seg.setDigits(d);
    seg.displayInt(0);
    delay(1000);
    seg.setDigits(d);
    seg.displayInt(8);
    delay(1000);
    seg.setDigits(d);
    seg.displayInt(-8);
    delay(1000);
  }
  for (int16_t d = 0; d <= 4; d++)
  {
    seg.setDigits(d);
    seg.displayInt(0);
    delay(1000);
    seg.setDigits(d);
    seg.displayInt(8);
    delay(1000);
    seg.setDigits(d);
    seg.displayInt(-8);
    delay(1000);
  }
  Serial.println();
  delay(1000);

  Serial.print("INT TEST 1:\t");
  seg.setDigits(1);
  for (int16_t counter = -200; counter < 1001; counter += 7)
  {
    seg.displayInt(counter);
    delay(100);
  }
  Serial.println();
  delay(1000);

  Serial.print("INT TEST 2:\t");
  seg.setDigits(4);
  for (int16_t counter = -200; counter < 1001; counter += 7)
  {
    seg.displayInt(counter);
    delay(100);
  }
  Serial.println();
  delay(1000);

}


// -- END OF FILE --

