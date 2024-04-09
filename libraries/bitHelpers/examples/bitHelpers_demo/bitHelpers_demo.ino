//
//    FILE: bitHelpers_demo.ino
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

  test_bitCount1_32_bits_variations();
  test_bitCount2();
  test_bitReverse();
  test_nybbleReverse();
  test_byteReverse();
  test_swap();
  test_bitFlip();
  test_bitRotateLeft();
  test_bitRotateRight();
  test_bitRot();

  Serial.println("\nDone...");
}


void loop()
{
}


//////////////////////////////////

void test_bitCount1_32_bits_variations()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  volatile uint8_t cnt;
  volatile uint32_t x = 0xFFFFFFFF;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    cnt = bitCountReference(x);
  }
  stop = micros();

  Serial.print(cnt);
  Serial.print("\t");
  Serial.print((stop - start) / 1000.0, 3);
  Serial.println("\tbitCountReference");
  delay(10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    cnt = bitCountKR(x);
  }
  stop = micros();

  Serial.print(cnt);
  Serial.print("\t");
  Serial.print((stop - start) / 1000.0, 3);
  Serial.println("\tbitCountKR");
  delay(10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    cnt = bitCountArray(x);
  }
  stop = micros();

  Serial.print(cnt);
  Serial.print("\t");
  Serial.print((stop - start) / 1000.0, 3);
  Serial.println("\tbitCountArray");
  delay(10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    cnt = bitCountF1(x);
  }
  stop = micros();

  Serial.print(cnt);
  Serial.print("\t");
  Serial.print((stop - start) / 1000.0, 3);
  Serial.println("\tbitCountF1");
  delay(10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    cnt = bitCountF2(x);
  }
  stop = micros();

  Serial.print(cnt);
  Serial.print("\t");
  Serial.print((stop - start) / 1000.0, 3);
  Serial.println("\tbitCountF2");
  Serial.println();
}


void test_bitCount2()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  volatile uint8_t cnt;
  volatile uint8_t a = 0xFF;
  volatile uint16_t b = 0xFFFF;
  volatile uint32_t c = 0xFFFFFFFF;
  volatile uint64_t d = 0xFFFFFFFFFFFFFFFF;

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    cnt = bitCount(a);
  }
  stop = micros();

  Serial.print(cnt);
  Serial.print("\t");
  Serial.print((stop - start) / 1000.0, 3);
  Serial.println("\tbitCount 8 bit");
  delay(10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    cnt = bitCount(b);
  }
  stop = micros();

  Serial.print(cnt);
  Serial.print("\t");
  Serial.print((stop - start) / 1000.0, 3);
  Serial.println("\tbitCount 16 bit");
  delay(10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    cnt = bitCount(c);
  }
  stop = micros();

  Serial.print(cnt);
  Serial.print("\t");
  Serial.print((stop - start) / 1000.0, 3);
  Serial.println("\tbitCount 32 bit");
  delay(10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    cnt = bitCount(d);
  }
  stop = micros();

  Serial.print(cnt);
  Serial.print("\t");
  Serial.print((stop - start) / 1000.0, 3);
  Serial.println("\tbitCount 64 bit");
  delay(10);

  Serial.println();
}


void test_bitReverse()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  uint8_t a = 0x17;
  a = bitReverse(a);
  Serial.println(a, HEX);
  a = bitReverse(a);
  Serial.println(a, HEX);

  uint16_t b = 0x1735;
  b = bitReverse(b);
  Serial.println(b, HEX);
  b = bitReverse(b);
  Serial.println(b, HEX);

  uint32_t x = 0x12345678;
  x = bitReverse(x);
  Serial.println(x, HEX);
  x = bitReverse(x);
  Serial.println(x, HEX);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = bitReverse(x);
  }
  stop = micros();

  Serial.print("    X:\t");
  Serial.println(x, HEX);
  Serial.print(" Time:\t");
  Serial.println((stop - start) / 1000.0, 3);
  Serial.println();
}


void test_nybbleReverse()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  uint8_t a = 0x17;
  a = nybbleReverse(a);
  Serial.println(a, HEX);
  a = nybbleReverse(a);
  Serial.println(a, HEX);

  uint16_t b = 0x1735;
  b = nybbleReverse(b);
  Serial.println(b, HEX);
  b = nybbleReverse(b);
  Serial.println(b, HEX);

  uint32_t x = 0x12345678;
  x = nybbleReverse(x);
  Serial.println(x, HEX);
  x = nybbleReverse(x);
  Serial.println(x, HEX);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = nybbleReverse(x);
  }
  stop = micros();

  Serial.print("    X:\t");
  Serial.println(x, HEX);
  Serial.print(" Time:\t");
  Serial.println((stop - start) / 1000.0, 3);
  Serial.println();
}


void test_byteReverse()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  uint16_t b = 0x1735;
  b = byteReverse(b);
  Serial.println(b, HEX);
  b = byteReverse(b);
  Serial.println(b, HEX);

  uint32_t x = 0x12345678;
  x = byteReverse(x);
  Serial.println(x, HEX);
  x = byteReverse(x);
  Serial.println(x, HEX);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = byteReverse(x);
  }
  stop = micros();

  Serial.print("    X:\t");
  Serial.println(x, HEX);
  Serial.print(" Time:\t");
  Serial.println((stop - start) / 1000.0, 3);
  Serial.println();
}


void test_swap()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  uint8_t a = 0x17;
  a = swap(a);
  Serial.println(a, HEX);
  a = swap(a);
  Serial.println(a, HEX);

  uint16_t b = 0x1735;
  b = swap(b);
  Serial.println(b, HEX);
  b = swap(b);
  Serial.println(b, HEX);

  uint32_t x = 0x12345678;
  x = swap(x);
  Serial.println(x, HEX);
  x = swap(x);
  Serial.println(x, HEX);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = swap(x);
  }
  stop = micros();

  Serial.print("   X:\t");
  Serial.println(x, HEX);
  Serial.print(" Time:\t");
  Serial.println((stop - start) / 1000.0, 3);
  Serial.println();
}


void test_bitFlip()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  uint32_t x = 0xFFFFFFFF;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    for (int j = 0; j < 32; j++)
    {
      x = bitFlip(x, j);
    }
  }
  stop = micros();

  Serial.print("    X:\t");
  Serial.println(x, HEX);
  Serial.print(" Time:\t");
  Serial.println((stop - start) / 1000.0 / 32, 3);
  Serial.println();
}


void test_bitRotateLeft()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  volatile uint32_t x = 0x12345678;
  for (int i = 0; i < 8; i++)
  {
    x = bitRotateLeft(x, 4);
    Serial.println(x, HEX);
  }

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    for (int j = 0; j < 32; j++)
    {
      x = bitRotateLeft(x, j);
    }
  }
  stop = micros();

  Serial.print("    X:\t");
  Serial.println(x, HEX);
  Serial.print(" Time:\t");
  Serial.println((stop - start) / 1000.0 / 32, 3);
  Serial.println();
}


void test_bitRotateRight()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  uint32_t x = 0x12345678;
  for (int i = 0; i < 8; i++)
  {
    x = bitRotateRight(x, 4);
    Serial.println(x, HEX);
  }

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    for (int i = 0; i < 32; i++)
    {
      x = bitRotateRight(x, i);
    }
  }
  stop = micros();

  Serial.print("    X:\t");
  Serial.println(x, HEX);
  Serial.print(" Time:\t");
  Serial.println((stop - start)  / 1000.0 / 32, 3);
  Serial.println();
}


void test_bitRot()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  uint32_t x = 0x12345678;
  for (int i = 0; i < 8; i++)
  {
    x = bitRot(x, i * 0.12);
    Serial.println(x, HEX);
  }
  x = 0xFFFFFFFF;
  Serial.print("    X:\t");
  Serial.println(x, HEX);
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = bitRot(x, 0.01);
  }
  stop = micros();

  Serial.print("    X:\t");
  Serial.println(x, HEX);
  Serial.print(" Time:\t");
  Serial.println((stop - start)  / 1000.0, 3);
  Serial.println();
}


//  -- END OF FILE --

