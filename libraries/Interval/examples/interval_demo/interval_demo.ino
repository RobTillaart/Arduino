//
//    FILE: interval_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal demo
//    DATE: 2020-07-21
//     URL: https://github.com/RobTillaart/Interval


#include "Interval.h"

Interval x(1, 2);
Interval y(2, 3);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();

  test_print();
  test_math_1();

  Serial.println("\nDone...");
}


void loop()
{
}


void test_print()
{
  Serial.println(__FUNCTION__);
  Serial.println(x);
  Serial.println(y);
  Serial.println();
}


void test_math_1()
{
  Serial.println(__FUNCTION__);
  Serial.println(x + y);
  Serial.println(x - y);
  Serial.println(x * y);
  Serial.println(x / y);
  Serial.println();

  Interval z = x;
  Serial.println(z);
  z += x;
  Serial.println(z);
  z -= x;
  Serial.println(z);
  z *= x;
  Serial.println(z);
  z /= x;
  Serial.println(z);

  Serial.println();
}


// -- END OF FILE --

