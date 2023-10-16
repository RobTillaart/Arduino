//
//    FILE: AD9833_multi_device.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo AD9833 wave form generator on 4 devices

#include "AD9833.h"

AD9833 AD[4];  //  4 devices.

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  //  each device needs its own select pin.
  AD[0].begin(4);   //  HW SPI, select pin 4
  AD[1].begin(5);
  AD[2].begin(6);
  AD[3].begin(7);

  //  A major chord
  AD[0].setFrequency(440.00, 0);     //  A
  AD[1].setFrequency(554.37, 0);     //  C#
  AD[2].setFrequency(659.25, 0);     //  E
  AD[3].setFrequency(880, 0);        //  A'

  //  build up chord in steps.
  AD[0].setWave(AD9833_SINE);
  delay(1000);
  AD[1].setWave(AD9833_SINE);
  delay(1000);
  AD[2].setWave(AD9833_SINE);
  delay(1000);
  AD[3].setWave(AD9833_SINE);
}


void loop()
{
}


//  -- END OF FILE --
