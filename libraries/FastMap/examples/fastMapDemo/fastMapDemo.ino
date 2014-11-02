//
//    FILE: fastMapDemo.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.02
// PURPOSE: demo of FastMap class ==> a faster map function
//    DATE: 2014-11-02
//     URL:
//
// Released to the public domain
//

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
  Serial.println(stop-start);
  Serial.print(z);
  Serial.print(" -> ");
  Serial.println(x);

  // GAIN
  Serial.print("Performance factor: ");
  Serial.println(reference/(stop-start));
}

void loop()
{
}
//
// END OF FILE
//