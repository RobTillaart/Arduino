//
//    FILE: AD524X_write_AD5241ino.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: AD524X demo program
//    DATE: 2020-12-08
//     URL: https://github.com/RobTillaart/AD524X
//

#include "AD524X.h"

AD5241 AD(0x2C);  // AD0 & AD1 == GND

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println(AD524X_VERSION);

  Wire.begin();
  Wire.setClock(400000);

  Serial.println(AD.pmCount());
}

void loop()
{
  for (int val = 0; val < 255; val++)
  {
    AD.write(0, val);
    if (val == 200)
    {
      AD.write(1, val, HIGH, LOW);
    }
    if (val == 0)
    {
      AD.write(0, val, LOW, LOW);
    }
    Serial.println(val);
    delay(20);
  }
}

// -- END OF FILE --
