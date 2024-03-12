//
//    FILE: TCA9555_getType.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test TCA9555 library - TCA9535 derived class
//     URL: https://github.com/RobTillaart/TCA9555


#include "TCA9555.h"


TCA9555 TCA0(0x20);
TCA9535 TCA1(0x21);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TCA9555_LIB_VERSION: ");
  Serial.println(TCA9555_LIB_VERSION);
  Serial.println();

  Wire.begin();
  TCA0.begin();
  TCA1.begin();

  Serial.println(TCA0.getType());
  Serial.println(TCA1.getType());

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
