//
//    FILE: timingTest.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: timing test for set class methods
//    DATE: 2014-11-09
//     URL: https://github.com/RobTillaart/SET


#include "set.h"


Set myset;
Set setA, setB;

uint32_t start;
uint32_t stop;

volatile bool b;


void setup()
{
  Serial.begin(115200);
  Serial.print("Start set_demo : ");
  Serial.println(SET_LIB_VERSION);
  Serial.println();

  Serial.println("\n\ntiming test");
  Serial.print("myset.clear():\t");
  start = micros();
  myset.clear();
  stop = micros();
  Serial.println(stop - start);

  Serial.print("myset.add():\t");
  start = micros();
  for (int i = 0; i < 256; i++) myset.add(i);
  stop = micros();
  Serial.println(stop - start);

  Serial.print("myset.sub():\t");
  start = micros();
  for (int i = 0; i < 256; i++) myset.sub(i);
  stop = micros();
  Serial.println(stop - start);

  Serial.print("myset.has():\t");
  start = micros();
  for (int i = 0; i < 256; i++) b = myset.has(i);
  stop = micros();
  Serial.println(stop - start);

  Serial.print("myset.invert(v):\t");
  start = micros();
  for (int i = 0; i < 256; i++) myset.invert(i);
  stop = micros();
  Serial.println(stop - start);

  Serial.print("myset.invert():\t");
  start = micros();
  myset.invert();
  stop = micros();
  Serial.println(stop - start);

  Serial.print("myset.count():\t");
  start = micros();
  myset.count();
  stop = micros();
  Serial.println(stop - start);

  Serial.println();

  Serial.println("done...");
  Serial.println();
}


void loop()
{
}


// -- END OF FILE --

