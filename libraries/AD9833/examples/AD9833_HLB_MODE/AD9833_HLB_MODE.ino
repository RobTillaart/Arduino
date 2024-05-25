//    FILE: AD9833_HLB_MODE.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test
//     URL: https://github.com/RobTillaart/AD9833/issues/10


#include "AD9833.h"

AD9833 AD(10, 11, 13);  // SW SPI UNO


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
  AD.setFrequency(1000, 0);
  AD.setFrequency(1000, 0);
  AD.setWave(2);
}


void loop()
{
  AD.writeFrequencyRegisterLSB(0, 10000);  //  931.32 Hz
  delay(2000);
  AD.writeFrequencyRegisterLSB(0, 5000);   //  466.66 Hz
  delay(2000);
}


//  -- END OF FILE --
