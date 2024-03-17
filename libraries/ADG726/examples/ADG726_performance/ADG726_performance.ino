//
//    FILE: ADG726_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: performance sketch
//     URL: https://github.com/RobTillaart/ADG725


#include "ADG726.h"


ADG726 ADG(4, 5, 6, 7, 8, 9, 10, 11);

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.print("ADG726_LIB_VERSION: ");
  Serial.println(ADG726_LIB_VERSION);
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
  for (int ch = 0; ch < 16; ch++)
  {
    ADG.setChannel(ch);

    Serial.print(ch);
    Serial.print("\t");
    Serial.println(ADG.getChannelA());
    delay(1000);
  }
}


//  -- END OF FILE --
