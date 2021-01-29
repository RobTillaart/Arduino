//
//    FILE: AD524X_sawtooth.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: AD524X demo program
//    DATE: 2013-10-12
//     URL: https://github.com/RobTillaart/AD524X
//

#include "AD524X.h"

AD524X AD01(0x2C);  // AD0 & AD1 == GND

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println(AD524X_VERSION);

  Wire.begin();
  Wire.setClock(400000);
}

void loop()
{
  for (int val = 0; val < 255; val++)
  {
    AD01.write(1, val);
    Serial.println(val);
    delay(20);
  }
}

// -- END OF FILE --
