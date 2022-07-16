//
//    FILE: INA226_demo_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-06-21
//     URL: https://github.com/RobTillaart/INA226
//
// Can be used for IDE-Tools->Plotter


#include "INA226.h"
#include "Wire.h"

INA226 INA(0x40);


void setup()
{
  Serial.begin(115200);

  Wire.begin();
  if (!INA.begin() )
  {
    Serial.println("could not connect. Fix and Reboot");
  }

  // 1 ampere - 0.002 shunt.
  INA.setMaxCurrentShunt(1, 0.002);

  Serial.println("POWER2 = busVoltage x current\n");
  Serial.println("BUS\tCURRENT\tPOWER\tPOWER2\tDELTA");
}


void loop()
{
  float bv = INA.getBusVoltage();
  // float sv = INA.getShuntVoltage_mV();
  float cu = INA.getCurrent_mA();
  float po = INA.getPower_mW();

  Serial.print(bv, 3);
  Serial.print("\t");
  Serial.print(cu, 3);
  Serial.print("\t");
  Serial.print(po, 3);
  Serial.print("\t");
  Serial.print(bv * cu, 3);
  Serial.print("\t");
  Serial.print((po - bv * cu), 3);
  Serial.println();
  delay(100);
}


// -- END OF FILE --

