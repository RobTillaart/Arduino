//
//    FILE: INA226_demo_2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/INA226


#include "INA226.h"


INA226 INA(0x40);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("INA226_LIB_VERSION: ");
  Serial.println(INA226_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (!INA.begin() )
  {
    Serial.println("could not connect. Fix and Reboot");
  }

  Serial.println();
  //  Serial.print("AVG:\t");
  //  Serial.println((int)INA.getAverage());
  INA.setAverage(2);
  //  Serial.print("MAN:\t");
  //  Serial.println(INA.getManufacturerID(), HEX);
  //  Serial.print("DIE:\t");
  //  Serial.println(INA.getDieID(), HEX);
  delay(100);

  INA.setMaxCurrentShunt(1, 0.002);

}


void loop()
{
  Serial.println("\nPOWER2 = busVoltage x current");
  Serial.println(" V\t mA \t mW \t mW \t mW");
  Serial.println("BUS\tCURRENT\tPOWER\tPOWER2\tDELTA");
  for (int i = 0; i < 20; i++)
  {
    float bv = INA.getBusVoltage();
    //  float sv = INA.getShuntVoltage_mV();
    float cu = INA.getCurrent_mA();
    float po = INA.getPower_mW();

    Serial.print(bv, 3);
    Serial.print("\t");
    Serial.print(cu, 3);
    Serial.print("\t");
    Serial.print(po, 2);
    Serial.print("\t");
    Serial.print(bv * cu, 2);
    Serial.print("\t");
    Serial.print((bv * cu) - po, 2);
    Serial.println();
    delay(50);
  }
}


//  -- END OF FILE --

