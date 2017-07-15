//
//    FILE: fastMapDemo4.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: demo of FastMap class ==> a faster map function
//    DATE: 2014-11-02
//     URL:
//
// Released to the public domain
//

// works only with 0.1.04

#include "FastMap.h"

uint32_t start;
uint32_t stop;
uint32_t reference;

volatile long zz = 3000, yy = 20000;
volatile float x;

FastMap mapper;

void setup()
{
  Serial.begin(115200);
  Serial.print("Start fastMapDemo\nlib version: ");
  Serial.println(FASTMAP_LIB_VERSION);
  Serial.println();

  // Get a non optimizable value;
  int z = analogRead(A0);

  // REFERENCE
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = map(z, 0, 1023, yy, zz);
  }
  stop = micros();
  reference = stop-start;
  Serial.print("map():\t");
  Serial.println(reference);
  Serial.print(z);
  Serial.print(" -> ");
  Serial.println(x);
  Serial.println();

  // FASTMAP
  mapper.init(0, 1023, yy, zz);
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = mapper.map(z);
  }
  stop = micros();
  Serial.print("fastmap.map():\t");
  Serial.println(stop-start);
  Serial.print(z);
  Serial.print(" -> ");
  Serial.println(x);

  // GAIN
  Serial.print("Performance factor: ");
  Serial.println((float)reference/(stop-start));
  Serial.println();
  
  // constrainedMap
  mapper.init(0, 1023, yy, zz);
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = mapper.constrainedMap(z);
  }
  stop = micros();
  Serial.print("fastmap.constrainedMap():\t");
  Serial.println(stop-start);
  Serial.print(z);
  Serial.print(" -> ");
  Serial.println(x);

  // GAIN
  Serial.print("Performance factor: ");
  Serial.println((float)reference/(stop-start));
  Serial.println();

 // lowerConstrainedMap
  mapper.init(0, 1023, yy, zz);
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = mapper.lowerConstrainedMap(z);
  }
  stop = micros();
  Serial.print("fastmap.lowerConstrainedMap():\t");
  Serial.println(stop-start);
  Serial.print(z);
  Serial.print(" -> ");
  Serial.println(x);

  // GAIN
  Serial.print("Performance factor: ");
  Serial.println((float)reference/(stop-start));
  Serial.println();

 // upperConstrainedMap
  mapper.init(0, 1023, yy, zz);
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = mapper.upperConstrainedMap(z);
  }
  stop = micros();
  Serial.print("fastmap.upperConstrainedMap():\t");
  Serial.println(stop-start);
  Serial.print(z);
  Serial.print(" -> ");
  Serial.println(x);

  // GAIN
  Serial.print("Performance factor: ");
  Serial.println((float)reference/(stop-start));
  Serial.println();


  Serial.println("done...");
}

void loop()
{
}
//
// END OF FILE
//
