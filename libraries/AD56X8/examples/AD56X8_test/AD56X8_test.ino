//
//    FILE: AD56X8_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test
//     URL: https://github.com/RobTillaart/AD56X8


#include "AD56X8.h"


AD56X8 AD16_HW(8);
AD56X8 AD16_SW(9, 10, 11);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD56X8_LIB_VERSION: ");
  Serial.println(AD56X8_LIB_VERSION);

  SPI.begin();
  AD16_HW.begin();
  AD16_SW.begin();

  Serial.print("HWSPI: ");
  Serial.println(AD16_HW.usesHWSPI());
  Serial.print("HWSPI: ");
  Serial.println(AD16_SW.usesHWSPI());
}


void loop()
{
}


//  -- END OF FILE --
