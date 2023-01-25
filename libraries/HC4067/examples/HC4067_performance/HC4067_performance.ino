//
//    FILE: HC4067_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for HC4067 16 channel (simple) multiplexer


#include "HC4067.h"

HC4067 mp(4, 5, 6, 7);

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HC4067 LIBRARY VERSION: ");
  Serial.println(HC4067_LIB_VERSION);
  Serial.println();

  delay(1000);
  start = micros();
  mp.setChannel(10);
  stop = micros();

  Serial.print("SetChannel: \t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  mp.setChannel(10);
  stop = micros();

  Serial.print("SetChannel: \t");
  Serial.println(stop - start);
  delay(100);

}


void loop()
{
}


//  -- END OF FILE --
