//
//    FILE: AD9833_1000_Hz.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2023-08-25
// PURPOSE: create a 1000 Hz reference signal

#include "AD9833.h"

AD9833 AD;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  AD.begin(10);
  AD.setFrequency(1000, 0);   
  Serial.println(AD.getFrequency(0));
  AD.setFrequencyChannel(0);
  
  AD.setPhase(0, 0);   
  Serial.println(AD.getPhase(0));
  AD.setPhaseChannel(0);

  AD.setWave(AD9833_SINE);
  Serial.println(AD.getWave());
}


void loop()
{
}


//  -- END OF FILE --
