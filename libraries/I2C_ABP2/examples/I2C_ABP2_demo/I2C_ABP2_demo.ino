//
//    FILE: I2C_ABP2_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/I2C_ABP2


#include "I2C_ABP2.h"


I2C_ABP2 pres(0x28);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("I2C_ABP2_LIB_VERSION: ");
  Serial.println(I2C_ABP2_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (pres.begin(0, 2.0) == false)
  {
    Serial.print("Error: Cannot find device: ");
    Serial.println(pres.getAddress());
  }

  pres.request();
}


void loop()
{
  if (millis() - pres.lastRead() > 1000)
  {
    pres.request();
    delay(10);
    if (I2C_ABP2_OK == pres.read())
    {
      Serial.print(pres.lastRead());
      Serial.print("\t");
      Serial.print(pres.getState(), HEX);
      Serial.print("\t");
      Serial.print(pres.getMilliBar(), 2);
      Serial.print("\t");
      Serial.print(pres.getCelsius(), 2);
      Serial.print("\n");
    }
  }
}


//  -- END OF FILE --
