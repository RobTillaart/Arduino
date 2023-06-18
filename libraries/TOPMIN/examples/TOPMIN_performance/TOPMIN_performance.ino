//
//    FILE: TOPMIN_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: TOPMAX demo
//     URL: https://github.com/RobTillaart/TOPMAX


#include "TOPMIN.h"

uint32_t start, stop;
uint32_t cnt = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TOPMIN_LIB_VERSION: ");
  Serial.println(TOPMIN_LIB_VERSION);
  Serial.println();

  for (int sz = 1; sz <= 128; sz *= 2)
  {
    test_fill(sz);
  }
  Serial.println();

  for (int sz = 1; sz <= 128; sz *= 2)
  {
    test_add(sz);
  }
  Serial.println();

  for (int sz = 1; sz <= 128; sz *= 2)
  {
    test_fill_ext(sz);
  }
  Serial.println();

  for (int sz = 1; sz <= 128; sz *= 2)
  {
    test_add_ext(sz);
  }
  Serial.println();

  Serial.println("done...");
}


void loop()
{
}


void test_fill(uint8_t sz)
{
  delay(100);
  TOPMIN tm(sz);
  start = micros();
  for (int i = 0; i < 1000; i++) tm.fill(i);
  stop = micros();
  Serial.print("FILL\t");
  Serial.print("size: ");
  Serial.print(sz);
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print((stop - start) * 0.001, 4);
  Serial.println();
}

void test_add(uint8_t sz)
{
  delay(100);
  TOPMIN tm(sz);

  start = micros();
  for (int i = 0; i < 1000; i++) tm.add(i);
  stop = micros();

  Serial.print("ADD\t");
  Serial.print("size: ");
  Serial.print(sz);
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print((stop - start) * 0.001, 4);
  Serial.println();
}


void test_fill_ext(uint8_t sz)
{
  delay(100);
  TOPMINext tm(sz);
  start = micros();
  for (int i = 0; i < 1000; i++) tm.fill(i, i);
  stop = micros();
  Serial.print("FILLext\t");
  Serial.print("size: ");
  Serial.print(sz);
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print((stop - start) * 0.001, 4);
  Serial.println();
}


void test_add_ext(uint8_t sz)
{
  delay(100);
  TOPMINext tm(sz);

  start = micros();
  for (int i = 0; i < 1000; i++) tm.add(i, i);
  stop = micros();

  Serial.print("ADDext\t");
  Serial.print("size: ");
  Serial.print(sz);
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print((stop - start) * 0.001, 4);
  Serial.println();
}


//  -- END OF FILE --
