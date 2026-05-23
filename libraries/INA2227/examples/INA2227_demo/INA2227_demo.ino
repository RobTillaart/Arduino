//
//    FILE: INA2227_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/INA2227


#include "INA2227.h"


INA2227 INA(0x40);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("INA2227_LIB_VERSION: ");
  Serial.println(INA2227_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (!INA.begin() )
  {
    Serial.println("could not connect. Fix and Reboot");
  }
  // INA.setMaxCurrentShunt(1, 0.002);

  Serial.print("Manufacturer:\t");
  Serial.println(INA.getManufacturerID());
  Serial.print("DeviceID:\t");
  Serial.println(INA.getDeviceID());
}


void loop()
{
  Serial.println("\nBUS\tSHUNT\tCURRENT\tPOWER");
  for (int i = 0; i < 10; i++)
  {
    Serial.print(INA.getBusVoltage(0), 3);
    Serial.print("\t");
    Serial.print(INA.getShuntVoltage_mV(0), 3);
    Serial.print("\t");
    Serial.print(INA.getCurrent_mA(0), 3);
    Serial.print("\t");
    Serial.print(INA.getPower_mW(0), 3);
    Serial.println();
    delay(1000);
  }
  Serial.println();

  Serial.println("\nBUS\tSHUNT\tCURRENT\tPOWER");
  for (int i = 0; i < 10; i++)
  {
    Serial.print(INA.getBusVoltage(1), 3);
    Serial.print("\t");
    Serial.print(INA.getShuntVoltage_mV(1), 3);
    Serial.print("\t");
    Serial.print(INA.getCurrent_mA(1), 3);
    Serial.print("\t");
    Serial.print(INA.getPower_mW(1), 3);
    Serial.println();
    delay(1000);
  }
  Serial.println();
}


//  -- END OF FILE --
