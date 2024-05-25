//    FILE: AD9833_switch_phase.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo AD9833 wave form generator
//     URL: https://github.com/RobTillaart/AD9833


#include "AD9833.h"


AD9833 AD(10);  //  HW SPI, select = pin 10

uint32_t lastTime = 0;
uint8_t  channel = 0;


void setup()
{
  Serial.begin(115200);
  while(!Serial);
  Serial.println(__FILE__);
  Serial.print("AD9833_LIB_VERSION: ");
  Serial.println(AD9833_LIB_VERSION);
  Serial.println();

  SPI.begin();

  AD.begin();

  AD.setWave(AD9833_SINE);
  AD.setFrequency(440, 0);    //  A0
  AD.setPhase(0, 0);
  AD.setPhase(90, 1); 
  AD.setPhaseChannel(channel);   

  AD.setWave(AD9833_SQUARE1);
  Serial.println(AD.getWave());
}


void loop()
{
  uint32_t now = millis();
  if (now - lastTime >= 1000)
  {
    lastTime = now;
    //  toggle channel.
    if (channel == 0) channel = 1;
    else channel = 0;
    AD.setPhaseChannel(channel); 
  }
}


//  -- END OF FILE --
