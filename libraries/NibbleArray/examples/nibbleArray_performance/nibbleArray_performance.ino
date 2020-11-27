//
//    FILE: nibbleArray_performance.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo performance nibble array
//    DATE: 2020-06-21
//     URL: https://github.com/RobTillaart/nibbleArray

// 0.1.0    2020-06-21 initial version
//
#include "nibbleArray.h"

nibbleArray na(500);

uint32_t start, stop, d1, d2;
volatile long x = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("NIBBLEARRAY_LIB_VERSION: ");
  Serial.println(NIBBLEARRAY_LIB_VERSION);

  // performance tests are run first once in a loop
  // then twice in a loop, so the difference is without
  // the loop overhead.
  test_size();
  test_get();
  test_set();
  test_clear();
  test_setAll();

  Serial.println("Done...");
}

void test_size()
{
  Serial.print("Nibble array size:\t");
  Serial.println(na.size());
  delay(100);
}

void test_get()
{
  Serial.println("\nget");
  start = micros();
  for (int i = 0; i < 500; i++)
  {
    x += na.get(i);
  }
  stop = micros();
  Serial.print("DURATION:\t");
  d1 = stop - start;
  Serial.println(d1);
  delay(100);

  start = micros();
  for (int i = 0; i < 500; i++)
  {
    x += na.get(i);
    x += na.get(i);
  }
  stop = micros();
  Serial.print("DURATION:\t");
  d2 = stop - start;
  Serial.println(d2);
  Serial.print("DELTA:\t\t");
  Serial.println(d2 - d1);
  Serial.print("       X:\t");
  Serial.println(x);
  delay(100);
}

void test_set()
{
  Serial.println("\nset");
  start = micros();
  for (int i = 0; i < 500; i++)
  {
    na.set(i, 5);
  }
  stop = micros();
  Serial.print("DURATION:\t");
  d1 = stop - start;
  Serial.println(d1);
  delay(100);

  start = micros();
  for (int i = 0; i < 500; i++)
  {
    na.set(i, 5);
    na.set(i, 10);
  }
  stop = micros();
  Serial.print("DURATION:\t");
  d2 = stop - start;
  Serial.println(d2);
  Serial.print("DELTA:\t\t");
  Serial.println(d2 - d1);
  delay(100);
}

void test_clear()
{
  Serial.println("\nclear");
  start = micros();
  na.clear();
  stop = micros();
  Serial.print("DURATION:\t");
  d1 = stop - start;
  Serial.println(d1);
  delay(100);

  start = micros();
  na.clear();
  na.clear();
  stop = micros();
  Serial.print("DURATION:\t");
  d2 = stop - start;
  Serial.println(d2);
  Serial.print("DELTA:\t\t");
  Serial.println(d2 - d1);
  delay(100);
  for (int i = 0; i < 500; i++)
  {
    if (na.get(i) != 0)
    {
      Serial.println("Error in clear");
    }
  }
  delay(100);
}

void test_setAll()
{
  Serial.println("\nsetAll");
  start = micros();
  na.setAll(1);
  stop = micros();
  Serial.print("DURATION:\t");
  d1 = stop - start;
  Serial.println(d1);
  delay(100);
  for (int i = 0; i < 500; i++)
  {
    if (na.get(i) != 1)
    {
      Serial.println("Error in setAll");
    }
  }
  delay(100);

  start = micros();
  na.setAll(2);
  na.setAll(3);
  stop = micros();
  Serial.print("DURATION:\t");
  d2 = stop - start;
  Serial.println(d2);
  Serial.print("DELTA:\t\t");
  Serial.println(d2 - d1);
  delay(100);
}

void loop()
{
}

// -- END OF FILE --
