//    FILE: AD9833_test_10.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test for issue 10
//     URL: https://github.com/RobTillaart/AD9833/issues/10


#include "AD9833.h"

AD9833 AD(10, 11, 13);


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
  AD.setFrequency(5000, 0);
  delay(10);
  AD.setFrequency(6000, 0);
  delay(10);
}


//  -- END OF FILE --
