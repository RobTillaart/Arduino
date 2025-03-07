//
//    FILE: INA260_multi_device.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo two INA260's
//     URL: https://github.com/RobTillaart/INA260
//
//  not tested with HW yet

#include "INA260.h"


INA260 INA0(0x40);
INA260 INA1(0x41);


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("INA260_LIB_VERSION: ");
  Serial.println(INA260_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (!INA0.begin() )
  {
    Serial.println("INA0 could not connect. Fix and Reboot");
  }
  if (!INA1.begin() )
  {
    Serial.println("INA1 could not connect. Fix and Reboot");
  }
}


void loop()
{
  Serial.println("\nBUS\tSHUNT\tCURRENT\tPOWER\t\tBUS\tSHUNT\tCURRENT\tPOWER");
  for (int i = 0; i < 20; i++)
  {
    Serial.print(INA0.getBusVoltage(), 3);
    Serial.print("\t");
    Serial.print(INA0.getShuntVoltage_mV(), 3);
    Serial.print("\t");
    Serial.print(INA0.getCurrent_mA(), 3);
    Serial.print("\t");
    Serial.print(INA0.getPower_mW(), 3);
    Serial.print("\t");
    Serial.print("\t");
    Serial.print(INA1.getBusVoltage(), 3);
    Serial.print("\t");
    Serial.print(INA1.getShuntVoltage_mV(), 3);
    Serial.print("\t");
    Serial.print(INA1.getCurrent_mA(), 3);
    Serial.print("\t");
    Serial.print(INA1.getPower_mW(), 3);
    Serial.println();
    delay(1000);
  }
}


//  -- END OF FILE --
