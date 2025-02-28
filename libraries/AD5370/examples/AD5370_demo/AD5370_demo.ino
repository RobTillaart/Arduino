//
//    FILE: AD5370_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/AD5370


#include "AD5370.h"
#include "SPI.h"

//  hardware SPI
//  (select, reset, clear, &SPI)  // latter optional
//  software SPI
//  (select, reset, clear, dataIn, dataOut, clock)
AD5370 dac40(8, 9, 10);  //  HW SPI


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD5370_LIB_VERSION: ");
  Serial.println(AD5370_LIB_VERSION);
  Serial.println();

  SPI.begin();
  dac40.begin();

  //  set reference values on first five lines.
  dac40.setDAC(0, 0);      //  00%
  dac40.setDAC(1, 16384);  //  25%
  dac40.setDAC(2, 32768);  //  50%
  dac40.setDAC(3, 49152);  //  75%
  dac40.setDAC(4, 65535);  //  100%
}


void loop()
{
  //  set continuous noise on the other lines.
  for (int i = 5; i < 40; i++)
  {
    dac40.setDAC(i, random(65536));
  }
  delay(1000);
}


//  -- END OF FILE --
