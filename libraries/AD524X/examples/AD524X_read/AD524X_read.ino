//
//    FILE: AD524X_read.ino
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
    Serial.print(val);
    AD01.write(1, val);
    delay(100);
    int x = AD01.read(1);
    Serial.print('\t');
    Serial.println(x);
    delay(100);
  }
  delay(1000);
}

// -- END OF FILE --
