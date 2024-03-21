//
//    FILE: ADG731_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: measure performance
//     URL: https://github.com/RobTillaart/ADG731


#include "ADG731.h"


ADG731 ADG(10, 11, 12);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.print("ADG731_LIB_VERSION: ");
  Serial.println(ADG731_LIB_VERSION);
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
