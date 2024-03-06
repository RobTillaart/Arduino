//
//    FILE: float16_test0.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test float16
//     URL: https://github.com/RobTillaart/float16


/*
   SIGN  EXP     MANTISSA
    0    01111    0000000000 = 1
    0    01111    0000000001 = 1 + 2−10 = 1.0009765625 (next smallest float after 1)
    1    10000    0000000000 = −2

    0    11110    1111111111 = 65504  (max half precision)

    0    00001    0000000000 = 2−14 ≈ 6.10352 × 10−5 (minimum positive normal)
    0    00000    1111111111 = 2−14 - 2−24 ≈ 6.09756 × 10−5 (maximum subnormal)
    0    00000    0000000001 = 2−24 ≈ 5.96046 × 10−8 (minimum positive subnormal)

    0    00000    0000000000 = 0
    1    00000    0000000000 = −0

    0    11111    0000000000 = infinity
    1    11111    0000000000 = −infinity

    0    01101    0101010101 = 0.333251953125 ≈ 1/3
*/


#include "float16.h"


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FLOAT16_LIB_VERSION: ");
  Serial.println(FLOAT16_LIB_VERSION);
  Serial.println("\nStart ");

  Serial.println();

  test_constructors();
  test_numbers();
  test_binary();
  test_toDouble();

  Serial.println("\ndone...");
}


void loop()
{
}


void test_constructors()
{
  Serial.println("\ntest_constructors:");
  float16 a;
  Serial.println(a.toDouble(), 9);
  Serial.println(a.getBinary(), HEX);

  float16 b = 6;
  Serial.println(b.toDouble(), 9);
  Serial.println(b.getBinary(), HEX);

  float16 e(EULER);
  Serial.println(e.toDouble(), 9);
  Serial.println(e.getBinary(), HEX);

  float16 f(e);
  Serial.println(f.toDouble(), 9);
  Serial.println(f.getBinary(), HEX);

  f = 1.61803398875;  // golden ratio
  Serial.println(f.toDouble(), 9);
  Serial.println(f.getBinary(), HEX);

  Serial.println();
}


void test_toDouble()
{
  Serial.println("\ntest_toDouble:");
  float16 f(3.1415);
  Serial.println(f.toDouble(), 9);  // 3.14
  f.setBinary(0x0000);
  Serial.println(f.toDouble(), 9);  // 0
  f.setBinary(0xFC00);
  Serial.println(f.toDouble(), 9);  //-inf
  f.setBinary(0x7C00);
  Serial.println(f.toDouble(), 9);  // inf
  f.setBinary(0x3C00);
  Serial.println(f.toDouble(), 9);  // 1
  f.setBinary(0x3C01);
  Serial.println(f.toDouble(), 9);  // 1.0009765625
  f.setBinary(0x3555);
  Serial.println(f.toDouble(), 9);  // 0.333333
  Serial.println();
}


void test_binary()
{
  Serial.println("\ntest_binary:");
  float16 e(3.1415);
  float16 f(0);
  Serial.println(e.toDouble(), 9);
  f.setBinary(e.getBinary());
  Serial.println(f.toDouble(), 9);
  Serial.println();
}


void test_numbers()
{
  Serial.println("\ntest_numbers:");
  Serial.println("** ZERO **");
  float16 a(0);
  Serial.println(a.toDouble(), 9);

  Serial.println("** SUBNORMAL **");
  float16 b(1 / 1000.0);
  Serial.println(b.toDouble(), 9);

  Serial.println("** NORMAL **");
  float16 c(1 / 2000.0);
  Serial.println(c.toDouble(), 9);

  c = 1/3.0;
  Serial.println(c.toDouble(), 9);

  float16 d(1);
  Serial.println(d.toDouble(), 9);

  float16 e(PI);
  Serial.println(e.toDouble(), 9);

  Serial.println("** OVERFLOW **");
  float16 f(1000000.0);
  Serial.println(f.toDouble(), 9);

  Serial.println("** UNDERFLOW **");
  float16 g(1 / 1000000.0);
  Serial.println(g.toDouble(), 9);

  Serial.println();
}


//  -- END OF FILE --
