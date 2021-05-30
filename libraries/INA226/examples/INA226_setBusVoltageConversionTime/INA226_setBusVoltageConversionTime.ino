//
//    FILE: INA226_BusVoltageConversionTime.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2021-05-18
//     URL: https://github.com/RobTillaart/INA226


#include "INA226.h"
#include "Wire.h"

INA226 INA(0x40);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();
  if (!INA.begin() )
  {
    Serial.println("could not connect. Fix and Reboot");
  }

  Serial.print("SHUNT:\t");
  Serial.println(INA.getShuntVoltage(), 2);
  Serial.print("  BUS:\t");
  Serial.println(INA.getBusVoltage(), 2);
  Serial.print("POWER:\t");
  Serial.println(INA.getPower(), 2);
  Serial.print(" CURR:\t");
  Serial.println(INA.getCurrent(), 2);

  Serial.println();
  Serial.print("MAN:\t");
  Serial.println(INA.getManufacturerID(), HEX);
  Serial.print("DIE:\t");
  Serial.println(INA.getDieID(), HEX);

  Serial.println("done...");
}


void loop()
{
  for (int bvct = 0; bvct < 8; bvct++)
  {
    INA.setBusVoltageConversionTime(bvct);
    Serial.print(bvct);
    Serial.print(INA.getBusVoltage(), 4);
    Serial.print("\t");
    Serial.print(INA.getShuntVoltage(), 4);
    Serial.print("\t");
    Serial.print(INA.getCurrent(), 4);
    Serial.print("\t");
    Serial.print(INA.getPower(), 4);
    Serial.println();
    delay(1000);
  }
}



// -- END OF FILE --
