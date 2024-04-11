//
//    FILE: boolArrayDemo0.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo performance reading boolean array
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
  Serial.println(__FILE__);
  Serial.print("BOOLARRAY_LIB_VERSION:\t");
  Serial.println(BOOLARRAY_LIB_VERSION);

  int rv = b.begin(2000);
  Serial.print("SIZE bits:\t");
  Serial.println(b.size());
  Serial.print("MEM bytes:\t");
  Serial.println(b.memory());
  Serial.print("freeMemory:\t");
  Serial.println(freeMemory());

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


#ifdef AVR

extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void *__brkval;

int freeMemory()
{
  int free_memory;

  if ((int)__brkval == 0)
    free_memory = ((int)&free_memory) - ((int)&__bss_end);
  else
    free_memory = ((int)&free_memory) - ((int)__brkval);

  return free_memory;
};

#else

int freeMemory()
{
  return 0;
};

#endif



//  -- END OF FILE --
