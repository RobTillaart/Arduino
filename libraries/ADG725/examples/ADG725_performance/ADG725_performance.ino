//
//    FILE: ADG725_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: measure performance
//     URL: https://github.com/RobTillaart/ADG725


#include "ADG725.h"


ADG725 ADG(10, 11, 12);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.print("ADG725_LIB_VERSION: ");
  Serial.println(ADG725_LIB_VERSION);
  delay(100);

  start = micros();
  for (int ch = 0; ch < 16; ch++)
  {
    ADG.setChannel(ch);
  }
  stop = micros();
  Serial.print("setChannel:\t");
  Serial.println((stop - start) / 16.0);
  delay(100);

  start = micros();
  for (int ch = 0; ch < 16; ch++)
  {
    ADG.setChannelA(ch);
  }
  stop = micros();
  Serial.print("setChannelA:\t");
  Serial.println((stop - start) / 16.0);
  delay(100);

  start = micros();
  for (int ch = 0; ch < 16; ch++)
  {
    ADG.setChannelB(ch);
  }
  stop = micros();
  Serial.print("setChannelB:\t");
  Serial.println((stop - start) / 16.0);
  delay(100);
}


void loop()
{
}


//  -- END OF FILE --
