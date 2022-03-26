//
//    FILE: waveMix_demo_adaptive_weight.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/WaveMix
//
// to be viewed by Serial plotter 

#include "WaveMix.h"

WaveMix wm;

float n = 0;
uint8_t perc = 0;

void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("WAVEMIX_LIB_VERSION: ");
  Serial.println(WAVEMIX_LIB_VERSION);

  wm.setPercentage(perc);
}


void loop()
{
  float squareWave = int(n) % 2;
  Serial.println(wm.mix(sin(n), squareWave) * 100);
  n = n + 0.05;
  if (n > perc)
  {
    perc++;
    if (perc == 101)
    {
      perc = 0;
      n = 0;
    }
    wm.setPercentage(perc);
  }
  // delay(10);
}


// -- END OF FILE --
