//
//    FILE: INA219_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/INA219


#include "INA219.h"

INA219 INA(0x40);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("INA219_LIB_VERSION: ");
  Serial.println(INA219_LIB_VERSION);

  Wire.begin();
  if (!INA.begin() )
  {
    Serial.println("could not connect. Fix and Reboot");
  }
}


void loop()
{
  //  these two can be read without further configuration.
  Serial.print(INA.getBusVoltage(), 3);
  Serial.print("\t");
  Serial.print(INA.getShuntVoltage_mV(), 3);
  Serial.println();
  delay(10);
}


//  -- END OF FILE --

