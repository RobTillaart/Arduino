//
//    FILE: boolArrayDemo2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo performance boolean array
//     URL: https://github.com/RobTillaart/BoolArray


#include "BoolArray.h"


BoolArray b;

uint32_t start;
uint32_t stop;
volatile long x = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("BOOLARRAY_LIB_VERSION:\t");
  Serial.println(BOOLARRAY_LIB_VERSION);

  b.begin(1000);

  Serial.print("Bool array size:\t");
  Serial.println(b.size());

  Serial.println("\nget");
  delay(10);
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x += b.get(i);
  }
  stop = micros();
  Serial.print("DURATION:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x += b.get(i);
    x += b.get(i);
  }
  stop = micros();
  Serial.print("DURATION:\t");
  Serial.println(stop - start);
  Serial.print("       X:\t");
  Serial.println(x);

  Serial.println("\nset");
  delay(10);
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    b.set(i, 0);
  }
  stop = micros();
  Serial.print("DURATION:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    b.set(i, 0);
    b.set(i, 0);
  }
  stop = micros();
  Serial.print("DURATION:\t");
  Serial.println(stop - start);

  Serial.println("\nclear");
  delay(10);
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    b.clear();
  }
  stop = micros();
  Serial.print("DURATION:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    b.clear();
    b.clear();
  }
  stop = micros();
  Serial.print("DURATION:\t");
  Serial.println(stop - start);

  Serial.println("\nsetAll");
  delay(10);
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    b.setAll(1);
  }
  stop = micros();
  Serial.print("DURATION:\t");
  Serial.println(stop - start);

  for (int i = 0; i < 1000; i++)
  {
    if (b.get(i) == 0) Serial.println("Error in clear()");
  }
  delay(10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    b.setAll(1);
    b.setAll(1);
  }
  stop = micros();
  Serial.print("DURATION:\t");
  Serial.println(stop - start);

  Serial.println("\ntoggle");
  delay(10);
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    b.toggle(i);
  }
  stop = micros();
  Serial.print("DURATION:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    b.toggle(i);
    b.toggle(i);
  }
  stop = micros();
  Serial.print("DURATION:\t");
  Serial.println(stop - start);

  Serial.println("Done...");
}


void loop()
{
}


//  -- END OF FILE --
