//
//    FILE: map2bits_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: map2bits demo
//     URL: https://github.com/RobTillaart/map2bits
//     URL: https://github.com/RobTillaart/printHelpers


#include "map2bits.h"
#include "printHelpers.h"

map2bits mb;

volatile uint32_t x = 0;
volatile uint64_t y = 0;

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MAP2BITS_LIB_VERSION: ");
  Serial.println(MAP2BITS_LIB_VERSION);
  Serial.println();
  delay(100);

  test16();
  test32();
  test64();
}


void loop()
{

}


void test16()
{
  mb.init(0, 1000, 10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = mb.map16(i);
  }
  stop = micros();
  Serial.println("1000 x map16 (full)");
  Serial.print("US: ");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println((stop - start) / 1000.0);
  Serial.print("X:  ");
  Serial.println(x);
  Serial.println();
  delay(100);

  mb.init(100, 200, 10);
  start = micros();
  for (int i = 0; i < 300; i++)
  {
    x = mb.map16(i);
  }
  stop = micros();
  Serial.println("3 x 100 x map16 (constrained)");
  Serial.print("US: ");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println((stop - start) / 300.0);
  Serial.print("X:  ");
  Serial.println(x);
  Serial.println();
  delay(100);
}

void test32()
{
  mb.init(0, 1000, 10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = mb.map32(i);
  }
  stop = micros();
  Serial.println("1000 x map32 (full)");
  Serial.print("US: ");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println((stop - start) / 1000.0);
  Serial.print("X:  ");
  Serial.println(x);
  Serial.println();
  delay(100);

  mb.init(100, 200, 10);
  start = micros();
  for (int i = 0; i < 300; i++)
  {
    x = mb.map32(i);
  }
  stop = micros();
  Serial.println("3 x 100 x map32 (constrained)");
  Serial.print("US: ");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println((stop - start) / 300.0);
  Serial.print("X:  ");
  Serial.println(x);
  Serial.println();
  delay(100);
}

void test64()
{
  mb.init(0, 1000, 10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    y = mb.map64(i);
  }
  stop = micros();
  Serial.println("1000 x map64 (full)");
  Serial.print("US: ");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println((stop - start) / 1000.0);
  Serial.print("Y:  ");
  Serial.println(print64(y));
  Serial.println();
  delay(100);

  mb.init(100, 200, 10);
  start = micros();
  for (int i = 0; i < 300; i++)
  {
    y = mb.map64(i);
  }
  stop = micros();
  Serial.println("3 x 100 x map64 (constrained)");
  Serial.print("US: ");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println((stop - start) / 300.0);
  Serial.print("Y:  ");
  Serial.println(print64(y));
  Serial.println();
  delay(100);

  Serial.println();
  Serial.println("Done...");
}


// -- END OF FILE --
