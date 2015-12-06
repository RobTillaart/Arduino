//
//    FILE: bitArrayDemo2.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: demo performance reading boolean array
//    DATE: 2015-12-06
//     URL: https://forum.arduino.cc/index.php?topic=361167.0
//
// Released to the public domain
//

#include "BitArray.h"

BitArray b;

uint32_t start;
uint32_t stop;
volatile long x = 0;

void setup()
{
  Serial.begin(115200);
  Serial.print("Start ");
  Serial.println(__FILE__);
  Serial.print("LIB VERSION:\t");
  Serial.println(BITARRAY_LIB_VERSION);

  b.begin(1, 10000);
  Serial.print("CAPACITY:\t");
  Serial.println(b.capacity());
  Serial.print("  MEMORY:\t");
  Serial.println(b.memory());
  Serial.print("    BITS:\t");
  Serial.println(b.bits());
  Serial.print("SEGMENTS:\t");
  Serial.println(b.segments());  
  
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x += b.get(i);
  }
  stop = micros();
  Serial.print("DURATION:\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x += b.get(i);
    x += b.get(i);
  }
  stop = micros();
  Serial.print("DURATION:\t");
  Serial.println(stop - start);
  Serial.print("       X:\t");
  Serial.println(x);

  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    b.set(i, 0);
  }
  stop = micros();
  Serial.print("DURATION:\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    b.set(i, 0);
    b.set(i, 0);
  }
  stop = micros();
  Serial.print("DURATION:\t");
  Serial.println(stop - start);

  Serial.println("Done...");
}

void loop()
{
}
