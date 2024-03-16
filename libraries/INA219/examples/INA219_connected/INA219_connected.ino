//
//    FILE: INA219_connected.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo array of INA219 sensors
//     URL: https://github.com/RobTillaart/INA219


#include "INA219.h"


INA219 arr_ina[16] =
{
  INA219(0x40), INA219(0x41), INA219(0x42), INA219(0x43),
  INA219(0x44), INA219(0x45), INA219(0x46), INA219(0x47),
  INA219(0x48), INA219(0x49), INA219(0x4A), INA219(0x4B),
  INA219(0x4C), INA219(0x4D), INA219(0x4E), INA219(0x4F),
};


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("INA219_LIB_VERSION: ");
  Serial.println(INA219_LIB_VERSION);

  Wire.begin();

  for (int i = 0; i < 16; i++)
  {
    if (! arr_ina[i].begin())
    {
      Serial.print("Could not connect:  ");
      Serial.print(i);
      Serial.print("\t");
      Serial.print(arr_ina[i].getAddress(), HEX);
      Serial.println();
    }
    else
    {
      Serial.print("Found: ");
      Serial.print(arr_ina[i].getAddress(), HEX);
      Serial.println();
    }
  }
}


void loop()
{
}


//  -- END OF FILE --
