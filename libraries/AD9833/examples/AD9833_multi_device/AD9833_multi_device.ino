//
//    FILE: AD9833_multi_device.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo AD9833 wave form generator on 4 devices
//     URL: https://github.com/RobTillaart/AD9833
//
//    TODO: test with hardware

#include "AD9833.h"


//  each device needs its own select pin.
AD9833 AD[4] = 
{
  AD9833(4),
  AD9833(5),
  AD9833(6),
  AD9833(7)
};  //  4 devices.


void setup()
{
  Serial.begin(115200);
  while(!Serial);
  Serial.println(__FILE__);
  Serial.print("AD9833_LIB_VERSION: ");
  Serial.println(AD9833_LIB_VERSION);
  Serial.println();

  SPI.begin();

  for (int i = 0; i < 3; i++)
  {
    AD[i].begin();
  }

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
