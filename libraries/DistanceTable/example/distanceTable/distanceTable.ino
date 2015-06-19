//
//    FILE: distanceTable.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: demo of memory efficient distance table class
//    DATE: 2015-06-18
//     URL: 
//
// Released to the public domain
//

#include "DistanceTable.h"

uint32_t freeRam()
{
  extern int __heap_start, *__brkval;
  int v;
  return (uint32_t) &v - (__brkval == 0 ? (uint32_t) &__heap_start : (uint32_t) __brkval);
};

DistanceTable dt(20);

uint32_t start;
uint32_t stop;

void setup()
{
  Serial.begin(115200);
  Serial.print("DistanceTable: ");
  Serial.println(DISTANCETABLE_LIB_VERSION);
  Serial.println("DistanceTable test 20x20: ");

  Serial.print("clear:\t");
  start = micros();
  dt.clear();
  stop = micros();
  Serial.println(stop - start);


  Serial.print("set:\t");
  start = micros();
  for (int i = 0; i < 20; i++)
  {
    for (int j = 0; j < 20; j++)
    {
      dt.set(i, j, i * j);
    }
  }
  stop = micros();
  Serial.println(stop - start);


  Serial.print("get:\t");
  int count = 0;
  start = micros();
  for (int i = 0; i < 20; i++)
  {
    for (int j = 0; j < 20; j++)
    {
      if ( dt.get(i, j) < 0.5 ) count++;
    }
  }
  stop = micros();
  Serial.println(stop - start);
  Serial.print("count:\t");
  Serial.println(count);

  Serial.print("ram:\t");
  Serial.println(freeRam());

  Serial.println();
  Serial.println("dump:\t");
  for (int i = 0; i < 20; i++)
  {
    for (int j = 0; j < 20; j++)
    {
      Serial.print( dt.get(i, j), 1);
      Serial.print("\t");
    }
    Serial.println();
  }

  Serial.println();
  Serial.println("dump:\t");
  dt.dump();

  Serial.println();
  Serial.println("done...");
}

void loop()
{
}


