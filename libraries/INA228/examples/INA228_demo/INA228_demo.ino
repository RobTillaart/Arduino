//
//    FILE: INA228_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo core functions
//     URL: https://github.com/RobTillaart/INA228


#include "INA228.h"


INA228 INA(0x40);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();
  Serial.print("INA228_LIB_VERSION: ");
  Serial.println(INA228_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (!INA.begin() )
  {
    Serial.println("Could not connect. Fix and Reboot");
    while(1);
  }
}


void loop()
{
  Serial.println("\nBUS\tSHUNT\tCURRENT\tPOWER\tTEMP");
  for (int i = 0; i < 20; i++)
  {
    Serial.print(INA.getBusVoltage(), 3);
    Serial.print("\t");
    Serial.print(INA.getShuntVoltage_mV(), 3);
    Serial.print("\t");
    Serial.print(INA.getCurrent_mA(), 3);
    Serial.print("\t");
    Serial.print(INA.getPower_mW(), 3);
    Serial.print("\t");
    Serial.print(INA.getTemperature(), 3);
    Serial.println();
    delay(1000);
  }
}


//  -- END OF FILE --
