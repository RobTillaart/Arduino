//
//    FILE: multimap_BS_compare.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2023-06-23


#include "MultiMap.h"

long in[100];
long out[100];

volatile int x;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MULTIMAP_LIB_VERSION: ");
  Serial.println(MULTIMAP_LIB_VERSION);
  Serial.println();
  delay(100);

  for (int i = 0; i < 100; i++)
  {
    in[i] = i * 11;
    out[i] = i * 7;
  }

  //  make sure print has ended
  delay(10);
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
  Serial.println(100000.0 * dur2 / dur1);
  delay(100);
}

//  -- END OF FILE --
