//
//    FILE: AD524X_midScaleReset.ino
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
  Serial.println(255);
  AD01.write(1, 255);
  delay(1000);

  Serial.println("reset");
  AD01.midScaleReset(1);
  delay(1000);

  Serial.println(0);
  AD01.write(1, 0);
  delay(1000);

  Serial.println("reset");
  AD01.midScaleReset(1);
  delay(1000);
}

// -- END OF FILE --
