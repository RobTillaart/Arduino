//
//    FILE: multimap_BS_compare.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo binary search - performance
//     URL: https://github.com/RobTillaart/MultiMap


#include "MultiMap.h"

long in[100];
long out[100];

volatile int x;


void setup()
{
  //  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MULTIMAP_LIB_VERSION: ");
  Serial.println(MULTIMAP_LIB_VERSION);
  Serial.println();

  for (int i = 0; i < 100; i++)
  {
    in[i] = i * 11;
    out[i] = i * 7;
  }

  Serial.println("size\tt1\tt2\tratio");
  //  make sure print has ended
  delay(100);
  for (int size = 4; size < 100; size++)
  {
    compare(size);
    delay(10);
  }
}


void loop()
{
}


void compare(uint8_t size)
{
  uint32_t start, dur1, dur2;

  start = micros();
  for (int i = 0; i < 1024; i++)
  {
    x = multiMap<long>(i, in, out, size);
  }
  dur1 = micros() - start;


  start = micros();
  for (int i = 0; i < 1024; i++)
  {
    x = multiMapBS<long>(i, in, out, size);
  }
  dur2 = micros() - start;
  Serial.print(size);
  Serial.print("\t");
  Serial.print(dur1);
  Serial.print("\t");
  Serial.print(dur2);
  Serial.print("\t");
  Serial.println(100.0 * dur2 / dur1);
  delay(25);
}


//  -- END OF FILE --
