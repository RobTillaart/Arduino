//
//    FILE: INA236_demoShuntVoltageConversionTime.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/INA236
//
//  run this sketch in the IDE plotter
//  change the setShuntVoltageConversionTime(7)  (line 33)   0..7
//  change the bus voltage
//  0 reads fast  ...  7 stair casing, slower reads)


#include "INA236.h"


INA236 INA(0x40);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("INA236_LIB_VERSION: ");
  Serial.println(INA236_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (!INA.begin() )
  {
    Serial.println("could not connect. Fix and Reboot");
  }
  INA.setMaxCurrentShunt(1, 0.002);
  INA.setShuntVoltageConversionTime(7);   //  <<<<<<<<<<<<<<<
}


void loop()
{
  Serial.print(INA.getShuntVoltageConversionTime());
  Serial.print("\t");
  Serial.print(INA.getShuntVoltage_uV(), 4);
  Serial.println();
  delay(100);
}


//  -- END OF FILE --

