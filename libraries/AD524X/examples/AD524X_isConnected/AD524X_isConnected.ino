//
//    FILE: AD524X_isConnected.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: AD524X demo program
//    DATE: 2021-01-27
//     URL: https://github.com/RobTillaart/AD524X
//


#include "AD524X.h"

AD524X AD01(0x2C);     //  AD0 & AD1 == GND


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println(AD524X_VERSION);

  Wire.begin();
  Wire.setClock(400000);

  bool b = AD01.begin();
  Serial.println(b?"true":"false");
  Serial.println(AD01.isConnected());

  Serial.println("\nDone...");
}


void loop()
{
}

// -- END OF FILE --
