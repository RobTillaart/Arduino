//    FILE: bitHelpers_bitRotFast_compare.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: performance comparison  (~30% faster)
//     URL: https://github.com/RobTillaart/bitHelpers


#include "bitHelpers.h"

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);

  test8();
  test16();
  test32();
  test64();
}


void test8()
{
  Serial.println();
  delay(10);
  uint8_t x8 = 0xFF;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x8 = bitRot(x8);
  }
  stop = micros();
  Serial.println(stop - start);
  Serial.println(x8, HEX);
  delay(10);

  x8 = 0xFF;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x8 = bitRotRef(x8);
  }
  stop = micros();
  Serial.println(stop - start);
  Serial.println(x8, HEX);
  delay(10);
}


void test16()
{
  Serial.println();
  delay(10);
  uint16_t x16 = 0xFF;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x16 = bitRot(x16);
  }
  stop = micros();
  Serial.println(stop - start);
  Serial.println(x16, HEX);
  delay(10);

  x16 = 0xFF;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x16 = bitRotRef(x16);
  }
  stop = micros();
  Serial.println(stop - start);
  Serial.println(x16, HEX);
  delay(10);
}


void test32()
{
  Serial.println();
  delay(10);
  uint32_t x32 = 0xFF;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x32 = bitRot(x32);
  }
  stop = micros();
  Serial.println(stop - start);
  Serial.println(x32, HEX);
  delay(10);

  x32 = 0xFF;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x32 = bitRotRef(x32);
  }
  stop = micros();
  Serial.println(stop - start);
  Serial.println(x32, HEX);
  delay(10);
}


void test64()
{
  Serial.println();
  delay(10);
  uint64_t x64 = 0xFF;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x64 = bitRot(x64);
  }
  stop = micros();
  Serial.println(stop - start);
  Serial.println((uint32_t)(x64 & 0xFFFFFFFF), HEX);
  delay(10);

  x64 = 0xFF;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x64 = bitRotRef(x64);
  }
  stop = micros();
  Serial.println(stop - start);
  Serial.println((uint32_t)(x64 >> 32), HEX);
  Serial.println((uint32_t)(x64 & 0xFFFFFFFF), HEX);
  delay(10);
}


void loop()
{
}

//  -- END OF FILE --
