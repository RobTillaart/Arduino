//
//    FILE: INA260_setBusVoltageConversionTime.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/INA260
//
//  run this sketch in the IDE plotter
//  change the setBusVoltageConversionTime(7)  (line 33)   0..7
//  change the bus voltage
//  0 reads fast  ...  7 stair-casing, slower reads)


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

  INA.setBusVoltageConversionTime(7);    //   <<<<<<<
}


void loop()
{
  Serial.print(INA.getBusVoltageConversionTime());
  Serial.print("\t");
  Serial.print(INA.getBusVoltage(), 4);
  Serial.println();
  delay(100);
}


//  -- END OF FILE --
