//
//    FILE: AD56X8_test_percentage.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test
//     URL: https://github.com/RobTillaart/AD56X8


#include "AD56X8.h"


AD5648 AD(8);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD56X8_LIB_VERSION: ");
  Serial.println(AD56X8_LIB_VERSION);

  SPI.begin();
  AD.begin();

  for (int chan = 0; chan < 8; chan++)
  {
    AD.setPercentage(chan, 8 * chan);
  }
  for (int chan = 0; chan < 8; chan++)
  {
    Serial.println(AD.getPercentage(chan));
  }
  Serial.print("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
