//
//    FILE: test_out_of_range.ino
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
  seg.begin();

  seg.displayOn();

  test_out_of_range();
}


void loop()
{
}


void test_out_of_range()
{
  bool b = true;

  b = seg.displayInt(-10000);
  seg.dumpSerial();
  Serial.print("displayInt(-10000):\t");
  Serial.println(b ? "true" : "false");
  delay(1000);
  b = seg.displayInt(10000);
  Serial.print("displayInt(10000):\t");
  Serial.println(b ? "true" : "false");
  delay(1000);

  b = seg.displayDate(100, 0);
  Serial.print("displayDate(100, 0):\t");
  Serial.println(b ? "true" : "false");
  delay(1000);
  b = seg.displayDate(00, 100);
  Serial.print("displayDate(0, 100):\t");
  Serial.println(b ? "true" : "false");
  delay(1000);
  b = seg.displayDate(100, 100);
  Serial.print("displayDate(100, 100):\t");
  Serial.println(b ? "true" : "false");
  delay(1000);

  b = seg.displayTime(100, 0);
  Serial.print("displayTime(100, 0):\t");
  Serial.println(b ? "true" : "false");
  delay(1000);
  b = seg.displayTime(00, 100);
  Serial.print("displayTime(0, 100):\t");
  Serial.println(b ? "true" : "false");
  delay(1000);
  b = seg.displayTime(100, 100);
  Serial.print("displayTime(100, 100):\t");
  Serial.println(b ? "true" : "false");
  delay(1000);

  b = seg.displaySeconds(6040);
  Serial.print("displaySeconds(6040):\t");
  Serial.println(b ? "true" : "false");
  delay(1000);

  b = seg.displayFloat(-1000);
  Serial.print("displayFloat(-1000):\t");
  Serial.println(b ? "true" : "false");
  delay(1000);
  b = seg.displayFloat(10000);
  Serial.print("displayFloat(10000):\t");
  Serial.println(b ? "true" : "false");
  delay(1000);

  b = seg.displayVULeft(9);
  Serial.print("displayVULeft(9):\t");
  Serial.println(b ? "true" : "false");
  delay(1000);
  b = seg.displayVURight(9);
  Serial.print("displayVURight(9):\t");
  Serial.println(b ? "true" : "false");
  delay(1000);

  b = seg.displayFixedPoint0(-1000);
  Serial.print("displayFixedPoint0(-1000):\t");
  Serial.println(b ? "true" : "false");
  delay(1000);
  b = seg.displayFixedPoint0(10000);
  Serial.print("displayFixedPoint0(10000):\t");
  Serial.println(b ? "true" : "false");
  delay(1000);

  b = seg.displayFixedPoint1(-100);
  Serial.print("displayFixedPoint1(-100):\t");
  Serial.println(b ? "true" : "false");
  delay(1000);
  b = seg.displayFixedPoint1(1000);
  Serial.print("displayFixedPoint1(1000):\t");
  Serial.println(b ? "true" : "false");
  delay(1000);

  b = seg.displayFixedPoint2(-10);
  Serial.print("displayFixedPoint2(-10):\t");
  Serial.println(b ? "true" : "false");
  delay(1000);
  b = seg.displayFixedPoint2(100);
  Serial.print("displayFixedPoint2(100):\t");
  Serial.println(b ? "true" : "false");
  delay(1000);

  b = seg.displayFixedPoint3(-0.001);
  Serial.print("displayFixedPoint3(-0.001):\t");
  Serial.println(b ? "true" : "false");
  delay(1000);
  b = seg.displayFixedPoint3(10);
  Serial.print("displayFixedPoint3(10):\t");
  Serial.println(b ? "true" : "false");
  delay(1000);
}


// -- END OF FILE --

