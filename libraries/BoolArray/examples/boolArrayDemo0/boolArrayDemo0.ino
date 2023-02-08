//
//    FILE: boolArrayDemo0.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo performance reading boolean array
//    DATE: 2015-12-06
//     URL: https://github.com/RobTillaart/BoolArray


#include "BoolArray.h"


BoolArray b;

uint32_t start;
uint32_t stop;
volatile long x = 0;

uint32_t duration1, duration2;


void setup()
{
  Serial.begin(115200);
  Serial.print("Start ");
  Serial.println(__FILE__);
  Serial.print("LIB VERSION:\t");
  Serial.println(BOOLARRAY_LIB_VERSION);

  int rv = b.begin(BOOLARRAY_MAXSIZE);
  Serial.print("SIZE:\t");
  Serial.println(b.size());

  if (rv != BOOLARRAY_OK)
  {
    Serial.println("Boolarray alloc error");
    while (1);
  }

  test0();
  test1();
  test2();
  test3();

  Serial.println("Done...");
}


void loop()
{
}


void test0()
{
  Serial.println();
  Serial.println("TEST SET(1)");
  delay(10);

  start = micros();
  for (int i = 0; i < BOOLARRAY_MAXSIZE; i++)
  {
    b.set(i, 1);
  }
  duration1 = micros() - start;
  Serial.print("DURATION:\t");
  Serial.println(duration1);
  delay(10);

  start = micros();
  for (int i = 0; i < BOOLARRAY_MAXSIZE; i++)
  {
    b.set(i, 1);
    b.set(i, 1);
  }
  duration2 = micros() - start;
  Serial.print("DURATION:\t");
  Serial.println(duration2);
  Serial.print("\t\t");
  Serial.print(duration2 - duration1);
  Serial.print("\t");
  Serial.println((duration2 - duration1) / (1.0 * b.size()));
}


void test1()
{
  Serial.println();
  Serial.println("TEST SET(0)");
  delay(10);

  start = micros();
  for (int i = 0; i < BOOLARRAY_MAXSIZE; i++)
  {
    b.set(i, 0);
  }
  duration1 = micros() - start;
  Serial.print("DURATION:\t");
  Serial.println(duration1);
  delay(10);

  start = micros();
  for (int i = 0; i < BOOLARRAY_MAXSIZE; i++)
  {
    b.set(i, 0);
    b.set(i, 0);
  }
  duration2 = micros() - start;
  Serial.print("DURATION:\t");
  Serial.println(duration2);
  Serial.print("\t\t");
  Serial.print(duration2 - duration1);
  Serial.print("\t");
  Serial.println((duration2 - duration1) / (1.0 * b.size()));
}


void test2()
{
  Serial.println();
  Serial.println("TEST GET(i)");
  delay(10);

  start = micros();
  for (int i = 0; i < BOOLARRAY_MAXSIZE; i++)
  {
    x += b.get(i);
  }
  duration1 = micros() - start;
  Serial.print("DURATION:\t");
  Serial.println(duration1);
  delay(10);

  start = micros();
  for (int i = 0; i < BOOLARRAY_MAXSIZE; i++)
  {
    x += b.get(i);
    x += b.get(i);
  }
  duration2 = micros() - start;
  Serial.print("DURATION:\t");
  Serial.println(duration2);
  Serial.print("\t\t");
  Serial.print(duration2 - duration1);
  Serial.print("\t");
  Serial.println((duration2 - duration1) / (1.0 * b.size()));
}


void test3()
{
  Serial.println();
  delay(10);

  start = micros();
  for (int i = 0; i < BOOLARRAY_MAXSIZE; i++)
  {
    b.set(i, 0);
  }
  duration1 = micros() - start;
  Serial.print("TEST SET(0):\t");
  Serial.println(duration1);
  delay(10);

  start = micros();
  b.setAll(0);
  duration2 = micros() - start;
  Serial.print("TEST SETALL(0):\t");
  Serial.println(duration2);
  Serial.print("FACTOR:\t\t");
  Serial.println(1.0 * duration1 / duration2);
  Serial.println();
  delay(10);

  start = micros();
  for (int i = 0; i < BOOLARRAY_MAXSIZE; i++)
  {
    b.set(i, 1);
  }
  duration1 = micros() - start;
  Serial.print("TEST SET(1):\t");
  Serial.println(duration1);
  delay(10);

  start = micros();
  b.setAll(1);
  duration2 = micros() - start;
  Serial.print("TEST SETALL(1):\t");
  Serial.println(duration2);
  Serial.print("FACTOR:\t\t");
  Serial.println(1.0 * duration1 / duration2);
}


//  -- END OF FILE --

