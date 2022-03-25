//
//    FILE: waveMix_demo.ino
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

  wm.setPercentage(25);
}


void loop()
{
  Serial.println(wm.mix(sin(n), abs(cos(2 * n))) * 100);
  n = n + 0.05;
  delay(10);
}


// -- END OF FILE --
