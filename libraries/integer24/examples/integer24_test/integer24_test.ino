//    FILE: integer24_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/integer24


#include "Arduino.h"
#include "integer24.h"


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("INTEGER24_LIB_VERSION: ");
  Serial.println(INTEGER24_LIB_VERSION);
  Serial.println();

  test_sizeOf();
  test_uint24_t();
  test_int24_t();
}


void loop()
{
}


void test_sizeOf()
{
  uint24_t a = 3;

  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.println(sizeof(uint24_t));
  Serial.println(sizeof(int24_t));
  Serial.println(sizeof(a));

  Serial.print("INT24_MAX: \t");
  Serial.println(INT24_MAX);
  Serial.print("UINT24_MAX: \t");
  Serial.println(UINT24_MAX);
}


void test_uint24_t()
{
  uint24_t a = 3, b = 2, c;

  Serial.println();
  Serial.println(__FUNCTION__);
  c = a + b;
  Serial.println((uint32_t)c);
  c = a - b;
  Serial.println((uint32_t)c);
  c = a * b;
  Serial.println((uint32_t)c);
  c = a / b;
  Serial.println((uint32_t)c);

  c = 0;
  Serial.println((uint32_t)c++);
  Serial.println((uint32_t)c--);
  Serial.println((uint32_t)--c);
  Serial.println((uint32_t)++c);

  c = sqrt(16);
  Serial.println((uint32_t)c);
  c = sqrt(c);
  Serial.println((uint32_t)c);
  c = exp(c);
  Serial.println((uint32_t)c);
  c = pow(c, 1.5);
  Serial.println((uint32_t)c);
}


void test_int24_t()
{
  int24_t a = -3, b = 2, c;

  Serial.println();
  Serial.println(__FUNCTION__);
  c = a + b;
  Serial.println((int32_t)c);
  c = a - b;
  Serial.println((int32_t)c);
  c = a * b;
  Serial.println((int32_t)c);
  c = a / b;
  Serial.println((int32_t)c);

  c = 0;
  Serial.println((int32_t)c++);
  Serial.println((int32_t)c--);
  Serial.println((int32_t)--c);
  Serial.println((int32_t)++c);

  c = sqrt(16);
  Serial.println((int32_t)c);
  c = sqrt(c);
  Serial.println((int32_t)c);
  c = exp(c);
  Serial.println((int32_t)c);
  c = pow(c, 1.5);
  Serial.println((int32_t)c);
}


//  -- END OF FILE --
