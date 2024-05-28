//
//    FILE: INA236_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo four INA236's, adjust to your sensor count
//     URL: https://github.com/RobTillaart/INA236
//
//  not tested with HW yet


#include "INA236.h"


#define INA_COUNT  4

INA236 INA[INA_COUNT] =
{
  INA236(0x40),
  INA236(0x41),
  INA236(0x42),
  INA236(0x43)
};


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("INA236_LIB_VERSION: ");
  Serial.println(INA236_LIB_VERSION);
  Serial.println();

  Wire.begin();
  bool failed = false;
  for (int ID = 0; ID < INA_COUNT; ID++)
  {
    if (!INA[ID].begin() )
    {
      failed = true;
      Serial.println(ID);
    }
    INA[ID].setMaxCurrentShunt(1, 0.002);
  }
  if (failed)
  {
    Serial.println("One or more INA could not connect. Fix and Reboot");
    while (1);
  }
}


void loop()
{
  Serial.println("\nID\tBUS\tSHUNT\tCURRENT\tPOWER");
  for (int i = 0; i < 20; i++)
  {
    for (int ID = 0; ID < 4; ID++)
    {
      Serial.print(ID);
      Serial.print("\t");
      Serial.print(INA[ID].getBusVoltage(), 3);
      Serial.print("\t");
      Serial.print(INA[ID].getShuntVoltage_mV(), 3);
      Serial.print("\t");
      Serial.print(INA[ID].getCurrent_mA(), 3);
      Serial.print("\t");
      Serial.print(INA[ID].getPower_mW(), 3);
      Serial.println();
      delay(1000);
    }
    Serial.println();
  }
}


//  -- END OF FILE --
