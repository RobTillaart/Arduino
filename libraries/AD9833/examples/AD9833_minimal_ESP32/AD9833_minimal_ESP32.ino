//
//    FILE: AD9833_minimal.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2023-08-25
// PURPOSE: demo AD9833 wave form generator


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
  Serial.println(__FILE__);

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
