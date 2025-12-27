//
//    FILE: INA238_dump_config.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test - dump configuration
//     URL: https://github.com/RobTillaart/INA238


#include "INA238.h"


INA238 INA(0x40);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("INA238_LIB_VERSION: ");
  Serial.println(INA238_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (!INA.begin() )
  {
    Serial.println("Could not connect. Fix and Reboot");
    while(1);
  }

  INA.setMaxCurrentShunt(10, 0.015);

  //  REGISTER 0
  Serial.print("ConversionDelay: ");
  Serial.println(INA.getConversionDelay());
  Serial.print("ADCRange: ");
  Serial.println(INA.getADCRange());
  Serial.println();

  //  REGISTER 1
  Serial.print("Mode: ");
  Serial.println(INA.getMode());
  Serial.print("BusVoltageConversionTime: ");
  Serial.println(INA.getBusVoltageConversionTime());
  Serial.print("ShuntVoltageConversionTime: ");
  Serial.println(INA.getShuntVoltageConversionTime());
  Serial.print("TemperatureConversionTime: ");
  Serial.println(INA.getTemperatureConversionTime());
  Serial.print("getAverage: ");
  Serial.println(INA.getAverage());
  Serial.println();


  Serial.print("\nDone");
}


void loop()
{
}


//  -- END OF FILE --
