//
//    FILE: boolArrayDemo2.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: demo performance boolean array
//    DATE: 2015-12-12
//     URL: https://forum.arduino.cc/index.php?topic=361167.0
//
// Released to the public domain
//
// 0.1.1 - added performance for toggle
//
#include "BoolArray.h"

BoolArray b;

uint32_t start;
uint32_t stop;
volatile long x = 0;

void setup()
{
  Serial.begin(115200);
  Serial.print("Start ");
  Serial.println(__FILE__);
  Serial.print("BOOLARRAY_LIB_VERSION:\t");
  Serial.println(BOOLARRAY_LIB_VERSION);

  b.begin(1000);

  Serial.println("\nget");
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x += b.get(i);
  }
  stop = micros();
  Serial.print("DURATION:\t");
  Serial.println(stop - start);

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
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    b.set(i, 0);
  }
  stop = micros();
  Serial.print("DURATION:\t");
  Serial.println(stop - start);

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
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    b.clear();
  }
  stop = micros();
  Serial.print("DURATION:\t");
  Serial.println(stop - start);

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
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    b.setAll(1);
  }
  stop = micros();
  Serial.print("DURATION:\t");
  Serial.println(stop - start);

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
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    b.toggle(i);
  }
  stop = micros();
  Serial.print("DURATION:\t");
  Serial.println(stop - start);

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