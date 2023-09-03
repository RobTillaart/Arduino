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

  AD.begin(10, 11, 13);  //  SW SPI over the HW SPI pins (UNO)
  //  AD.begin(10);      //  HW SPI 

  AD.setWave(AD9833_SQUARE1);
  Serial.println(AD.getWave());

  AD.setFrequency(1000.0, 0);
  Serial.println(AD.getFrequency(0));
  AD.setFrequencyChannel(0);
}


void loop()
{
}


//  -- END OF FILE --
