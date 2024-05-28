//
//    FILE: INA236_demo_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/INA236
//
// Can be used for IDE-Tools->Plotter


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

  //  1 ampere - 0.002 ohm shunt.
  INA.setMaxCurrentShunt(1, 0.002);

  Serial.println("POWER2 = busVoltage x current\n");
  Serial.println("BUS\tCURRENT\tPOWER\tPOWER2\tDELTA");
}


void loop()
{
  float bv = INA.getBusVoltage();
  //  float sv = INA.getShuntVoltage_mV();
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


//  -- END OF FILE --

