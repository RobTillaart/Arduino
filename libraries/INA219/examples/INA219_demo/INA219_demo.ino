//
//    FILE: INA219_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-05-18
//     URL: https://github.com/RobTillaart/INA219


#include "INA219.h"
#include "Wire.h"

INA219 INA(0x40);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("INA219_LIB_VERSION: ");
  Serial.println(INA219_LIB_VERSION);

  Wire.begin();
  if (!INA.begin() )
  {
    Serial.println("could not connect. Fix and Reboot");
  }
  INA.setMaxCurrentShunt(1, 0.002);
  delay(1000);
  INA.setMaxCurrentShunt(2.5, 0.002);
  delay(1000);
  INA.setMaxCurrentShunt(5, 0.002);
  delay(1000);
  INA.setMaxCurrentShunt(7.5, 0.002);
  delay(1000);
  INA.setMaxCurrentShunt(10, 0.002);
  delay(1000);
  INA.setMaxCurrentShunt(15, 0.002);
  delay(1000);
  INA.setMaxCurrentShunt(20, 0.002);
  delay(10000);
}


void loop()
{
  Serial.println("\nBUS\tSHUNT\tCURRENT\tPOWER");
  for (int i = 0; i < 20; i++)
  {
    Serial.print(INA.getBusVoltage(), 3);
    Serial.print("\t");
    Serial.print(INA.getShuntVoltage_mV(), 3);
    Serial.print("\t");
    Serial.print(INA.getCurrent_mA(), 3);
    Serial.print("\t");
    Serial.print(INA.getPower_mW(), 3);
    Serial.println();
    delay(1000);
  }
  delay(10000);
}


// -- END OF FILE --
