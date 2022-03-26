//
//    FILE: waveMix_demo_modulator.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/WaveMix
//
//  modulated sinus signal
//  view with serial plotter

#include "WaveMix.h"

WaveMix wm;

float modulate = 0.30;     // square wave modulate = 1.0 - dutyCyle


void setup()
{
  Serial.begin(230400);
  Serial.println(__FILE__);
  Serial.print("WAVEMIX_LIB_VERSION: ");
  Serial.println(WAVEMIX_LIB_VERSION);

  wm.setWeight(95, 5);  // 5% noise add.
  wm.setGain(100);
}


void loop()
{
  uint32_t start = millis();
  float n = 0;
  while (n < (2 * PI))
  {
    //  square modulation with setGain();
    if ((PI * modulate) < n && n < PI) wm.setGain(100);
    else if ((PI * (1 + modulate)) < n) wm.setGain(100);
    else wm.setGain(0);

    //  mix the signals
    Serial.println(wm.mix(sin(n), random(10) * 0.1));

    // stepsize determines frequency (numbers UNO)
    //  0.01 =>  ~5 Hz
    //  0.1  => ~25 Hz
    n = n + 0.1;
  }
  n = 0;
  // modulate += 0.05;
  if (modulate >= 1.0) modulate = 0;
  Serial.print("\t\t\t\tMILLIS:\t");
  Serial.println(millis() - start);
}


// -- END OF FILE --
