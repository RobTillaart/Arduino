//
//    FILE: AD9833_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo AD9833 wave form generator
//     URL: https://github.com/RobTillaart/AD9833


#include "AD9833.h"

#ifndef ESP32
#error ESP32 only example, please select appropriate board
#endif


//  HSPI uses default   SCLK=14, MISO=12, MOSI=13, SELECT=15
//  VSPI uses default   SCLK=18, MISO=19, MOSI=23, SELECT=5
SPIClass * myspi = new SPIClass(VSPI);
AD9833 AD(5, myspi);
//  AD9833 AD(15, 13, 14); //  SW SPI


void setup()
{
  Serial.begin(115200);
  while(!Serial);
  Serial.println(__FILE__);
  Serial.print("AD9833_LIB_VERSION: ");
  Serial.println(AD9833_LIB_VERSION);
  Serial.println();

  myspi->begin();

  AD.begin();
  AD.setFrequency(1000, 0);   //  1000 Hz.

  AD.setWave(AD9833_SQUARE1);
  Serial.println(AD.getWave());
}


void loop()
{
}


//  -- END OF FILE --
