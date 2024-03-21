//
//    FILE: ADG732_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: measure performance
//     URL: https://github.com/RobTillaart/ADG732


#include "ADG732.h"


ADG732 ADG(4, 5, 6, 7, 8, 9, 10, 11);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.print("ADG732_LIB_VERSION: ");
  Serial.println(ADG732_LIB_VERSION);
  delay(100);

  start = micros();
  for (int ch = 0; ch < 32; ch++)
  {
    ADG.setChannel(ch);
  }
  stop = micros();
  Serial.print("setChannel:\t");
  Serial.println((stop - start) / 32.0);
  delay(100);

}


void loop()
{
}


//  -- END OF FILE --
