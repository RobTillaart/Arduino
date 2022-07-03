//
//    FILE: DEVRANDOM_compile_time_random_seed.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo compile time random seed
//    DATE: 2020-06-23
//    (c) : MIT
//


#include "DEVRANDOM.h"

DEVRANDOM dr;

uint32_t i = 0, start, stop;
volatile int x;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();

  //  setup compile time random seed
  dr.print(__FILE__);
  dr.print(__DATE__);
  dr.print(__TIME__);
}


void loop()
{
  i++;
  if (dr.available())
  {
    Serial.print("\t");
    Serial.print(dr.read());
    if ((i % 10) == 9 ) Serial.println();
  }
  delay(100);
}


// -- END OF FILE --
