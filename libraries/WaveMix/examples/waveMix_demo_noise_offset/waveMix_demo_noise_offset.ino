//
//    FILE: waveMix_demo_noise_offset.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/WaveMix
//


#include "WaveMix.h"

WaveMix wm;

float n = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("WAVEMIX_LIB_VERSION: ");
  Serial.println(WAVEMIX_LIB_VERSION);

  wm.setPercentage(95);
}


void loop()
{
  Serial.println(wm.mix(sin(n), random(1000) * 0.001) * 100);
  n = n + 0.05;
  delay(10);
  wm.setOffset(int(n/20));  // just a demo
}


// -- END OF FILE --
