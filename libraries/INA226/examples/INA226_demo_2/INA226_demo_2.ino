//
//    FILE: INA226_demo_2.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: demo
//    DATE: 2021-06-21
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

  Serial.println();
  Serial.print("MAN:\t");
  Serial.println(INA.getManufacturerID(), HEX);
  Serial.print("DIE:\t");
  Serial.println(INA.getDieID(), HEX);
  delay(100);
  INA.setMaxCurrentShunt(1, 0.002);
  Serial.print("LSB:\t");
  Serial.println(INA.getCurrentLSB(), 10);
  Serial.println("\n\n");

  Serial.println("POWER2 = busVoltage x current\n");
  Serial.println("BUS\tCURRENT\tPOWER\tPOWER2");
}


void loop()
{
  float bv = INA.getBusVoltage();
  float sv = INA.getShuntVoltage_mV();
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
