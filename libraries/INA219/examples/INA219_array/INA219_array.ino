//
//    FILE: INA219_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo array of INA219 sensors
//     URL: https://github.com/RobTillaart/INA219


#include "INA219.h"

INA219 INA(0x40);

INA219 arr_ina[3] = { INA219(0x40), INA219(0x41), INA219(0x42) };


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("INA219_LIB_VERSION: ");
  Serial.println(INA219_LIB_VERSION);

  Wire.begin();

  for (int i = 0; i < 3; i++)
  {
    if (! arr_ina[i].begin())
    {
      Serial.print("Could not connect:  ");
      Serial.print(i);
      Serial.println(". Fix and Reboot");
    }
  }

  for (int i = 0; i < 3; i++)
  {
    arr_ina[i].setMaxCurrentShunt(5, 0.002);
    delay(1000);
    Serial.println(arr_ina[i].getBusVoltageRange());
  }
}


void loop()
{
  Serial.println("\n\t#\tBUS\t\tSHUNT\t\tCURRENT\t\tPOWER\t\tOVF\t\tCNVR");
  for (int i = 0; i < 3; i++)
  {
    Serial.print("\t");
    Serial.print(i);
    Serial.print("\t");
    Serial.print(arr_ina[i].getBusVoltage(), 2);
    Serial.print("\t\t");
    Serial.print(arr_ina[i].getShuntVoltage_mV(), 2);
    Serial.print("\t\t");
    Serial.print(arr_ina[i].getCurrent_mA(), 2);
    Serial.print("\t\t");
    Serial.print(arr_ina[i].getPower_mW(), 2);
    Serial.print("\t\t");
    Serial.print(arr_ina[i].getMathOverflowFlag());
    Serial.print("\t\t");
    Serial.print(arr_ina[i].getConversionFlag());
    Serial.println();
    delay(1000);
  }
  delay(1000);
}


//  -- END OF FILE --
