//
//    FILE: bitHelpers_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/bitHelpers


#include "bitHelpers.h"

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println();

  test_32_bit();
  test_24_bit();

  Serial.println("\nDone...");
}


void loop()
{
}


//////////////////////////////////

void test_24_bit()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  uint32_t x = 0x9B3FAA;
  uint32_t y = byteReverse(x);
  uint32_t z = byteReverse(x) >> 8;
  Serial.println(x, HEX);
  Serial.println(y, HEX);
  Serial.println(z, HEX);
  Serial.println();

  printHex32(y);
  printHex32(z);
  Serial.println();

  x = 0x5D9504;
  y = byteReverse(x);
  z = byteReverse(x) >> 8;
  Serial.println(x, HEX);
  Serial.println(y, HEX);
  Serial.println(z, HEX);
  Serial.println();

  Serial.println();
}


void test_32_bit()
{
  Serial.println();
  Serial.println(__FUNCTION__);


  Serial.println();
}


void printHex16(uint16_t x)
{
  if (x < 0x1000) Serial.print('0');
  if (x < 0x100)  Serial.print('0');
  if (x < 0x10)   Serial.print('0');
  Serial.println(x, HEX);
}


void printHex24(uint32_t x)
{
  if (x < 0x100000)  Serial.print('0');
  if (x < 0x10000)   Serial.print('0');
  if (x < 0x1000) Serial.print('0');
  if (x < 0x100)  Serial.print('0');
  if (x < 0x10)   Serial.print('0');
  Serial.println(x, HEX);
}


void printHex32(uint32_t x)
{
  if (x < 0x10000000) Serial.print('0');
  if (x < 0x1000000) Serial.print('0');
  if (x < 0x100000)  Serial.print('0');
  if (x < 0x10000)   Serial.print('0');
  if (x < 0x1000) Serial.print('0');
  if (x < 0x100)  Serial.print('0');
  if (x < 0x10)   Serial.print('0');
  Serial.println(x, HEX);
}



//  -- END OF FILE --
