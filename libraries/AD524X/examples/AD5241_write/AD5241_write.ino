//
//    FILE: AD5241_write.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: AD5241 demo program - single channel!
//     URL: https://github.com/RobTillaart/AD524X


#include "AD524X.h"

AD5280 AD01(0x2C);  //  AD0 & AD1 == GND


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD524X_LIB_VERSION: ");
  Serial.println(AD524X_LIB_VERSION);

  Wire.begin();
  Wire.setClock(400000);

  bool b = AD01.begin();
  Serial.println(b ? "true" : "false");
  Serial.println(AD01.isConnected());
}


void loop()
{
  for (int val = 0; val < 255; val++)
  {
    AD01.write(val);
    if (val == 200)
    {
      AD01.write(val, HIGH, LOW);
    }
    if (val == 0)
    {
      AD01.write(val, LOW, HIGH);
    }
    Serial.println(val);
    delay(20);
  }
}


//  -- END OF FILE --
