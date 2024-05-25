//
//    FILE: AD9833_1000_Hz.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: create a 1000 Hz reference signal
//     URL: https://github.com/RobTillaart/AD9833


#include "AD9833.h"


AD9833 AD(10, 11, 13);  //  SW SPI over the HW SPI pins (UNO);
//  AD(10);      //  HW SPI 


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
