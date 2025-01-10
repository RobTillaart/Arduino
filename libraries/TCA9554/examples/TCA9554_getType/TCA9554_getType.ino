//
//    FILE: TCA9554_getType.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test TCA9554 library
//     URL: https://github.com/RobTillaart/TCA9554


#include "TCA9554.h"


TCA9554 TCA(0x20);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TCA9554_LIB_VERSION: ");
  Serial.println(TCA9554_LIB_VERSION);
  Serial.println();

  Wire.begin();
  TCA.begin();

  Serial.println(TCA.getType());


  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
