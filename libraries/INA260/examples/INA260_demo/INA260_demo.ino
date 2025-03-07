//
//    FILE: INA260_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/INA260


#include "INA260.h"


INA260 INA(0x40);


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("INA260_LIB_VERSION: ");
  Serial.println(INA260_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (!INA.begin() )
  {
    Serial.println("could not connect. Fix and Reboot");
  }
}


void loop()
{
  Serial.println("\nBUS\tSHUNT\tCURRENT\tPOWER");
  for (int i = 0; i < 20; i++)
  {
    Serial.print(INA.getBusVoltage(), 3);
    Serial.print("\t");
    Serial.print(INA.getShuntVoltage_mV(), 3);
    Serial.print("\t");
    Serial.print(INA.getCurrent_mA(), 3);
    Serial.print("\t");
    Serial.print(INA.getPower_mW(), 3);
    Serial.println();
    delay(1000);
  }
}


//  -- END OF FILE --
