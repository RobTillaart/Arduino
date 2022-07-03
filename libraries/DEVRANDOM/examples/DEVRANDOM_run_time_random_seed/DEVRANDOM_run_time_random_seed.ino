//
//    FILE: DEVRANDOM_run_time_random_seed.ino
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
  Serial.println();
  Serial.println(__FILE__);
  Serial.println();

  //  setup compile time random seed
  //  dr.print(__FILE__);
  //  dr.print(__DATE__);
  //  dr.print(__TIME__);

  //  setup run time random seed
  Serial.println("send 8 chars");
  for (int i = 0; i < 8; i++)
  {
    while (Serial.available() == 0);
    dr.print(Serial.read(), HEX);
    dr.print(micros() * (micros() << 7));
    dr.read();  // flush intermediate results
  }
  //  flush input
  while (Serial.available()) Serial.read();
}


void loop()
{
  i++;
  if (dr.available())
  {
    Serial.print("\t");
    Serial.print(dr.read());
    if ((i % 10) == 0 ) Serial.println();
  }
  delay(100);
}


// -- END OF FILE --
