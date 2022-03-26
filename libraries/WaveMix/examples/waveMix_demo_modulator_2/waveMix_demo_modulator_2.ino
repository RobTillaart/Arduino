//
//    FILE: waveMix_demo_modulator_2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/WaveMix
//
//  modulated sinus signal
//  view with serial plotter

#include "WaveMix.h"

WaveMix wm;
float n = 0;

void setup()
{
  Serial.begin(230400);
  Serial.println(__FILE__);
  Serial.print("WAVEMIX_LIB_VERSION: ");
  Serial.println(WAVEMIX_LIB_VERSION);

  wm.setWeight(1, 0);
  wm.setGain(100);
}


void loop()
{
  wm.setGain(100 * sin(n * 0.03));  //  modulating sinus
  Serial.println(wm.mix(sin(n)));  //  signal sinus.
  n = n + 0.3;
}


// -- END OF FILE --
