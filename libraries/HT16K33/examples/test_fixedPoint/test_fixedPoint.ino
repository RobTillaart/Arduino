//
//    FILE: test_fixedPoint.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test decimal point for floats.
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

  if (! seg.begin())
  {
    Serial.println("not connected");
  }

  seg.displayOn();

  seg.displayFixedPoint0(1.945);
  delay(1000);
  seg.displayFixedPoint1(1.945);
  delay(1000);
  seg.displayFixedPoint2(1.945);
  delay(1000);
  seg.displayFixedPoint3(1.945);
  delay(1000);
}


void loop()
{
  test_printFixedPoint();
  Serial.println("---------------");
  delay(1000);
}


void test_printFixedPoint()
{
  for (int i = -2000; i < 2000; i++)
  {
    float f = i * 0.001;
    seg.displayFixedPoint3(f);
    delay(2);
  }

  for (int i = -2000; i < 2000; i++)
  {
    float f = i * 0.001;
    seg.displayFixedPoint2(f);
    delay(2);
  }

  for (int i = -2000; i < 2000; i++)
  {
    float f = i * 0.001;
    seg.displayFixedPoint1(f);
    delay(2);
  }

  for (int i = -2000; i < 2000; i++)
  {
    float f = i * 0.001;
    seg.displayFixedPoint0(f);
    delay(2);
  }
}


// -- END OF FILE --

