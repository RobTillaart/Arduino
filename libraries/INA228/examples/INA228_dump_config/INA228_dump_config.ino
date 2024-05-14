//
//    FILE: INA228_dump_config.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test - dump configuration
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

  //  REGISTER 0
  Serial.print("Accumulation: ");
  Serial.println(INA.getAccumulation());
  Serial.print("ConversionDelay: ");
  Serial.println(INA.getConversionDelay());
  Serial.print("TemperatureCompensation: ");
  Serial.println(INA.getTemperatureCompensation());
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


  Serial.print("\n done");
}


void loop()
{
}


//  -- END OF FILE --
