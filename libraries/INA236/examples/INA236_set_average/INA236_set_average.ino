//
//    FILE: INA236_set_average.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/INA236
//
//  run this sketch in the IDE plotter
//  change the setAverage(7)  (line 33)   0..7
//  change the bus voltage
//  0 reads fast  ...  7 stair casing, very slow


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
  INA.setAverage(INA236_1024_SAMPLES);   //  <<<<<<<<<<<<<<<
}


void loop()
{
  Serial.print("\t");
  Serial.print(INA.getAverage());
  Serial.print("\t");
  Serial.print(INA.getBusVoltage(), 4);
  Serial.print("\t");
  Serial.print(INA.getShuntVoltage_mV(), 4);
  Serial.println();
  delay(100);
}


//  -- END OF FILE --

