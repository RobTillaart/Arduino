//
//    FILE: AD9833_minimal.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2023-08-25
// PURPOSE: demo AD9833 wave form generator


#include "AD9833.h"


AD9833 AD(10);  //  HW SPI, select pin 10


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  SPI.begin();

  AD.begin();
  AD.setFrequency(1000, 0);   //  1000 Hz.

  AD.setWave(AD9833_SQUARE1);
  Serial.println(AD.getWave());
}


void loop()
{
}


//  -- END OF FILE --
