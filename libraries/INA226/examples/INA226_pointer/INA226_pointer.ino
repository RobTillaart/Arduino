//
//    FILE: INA226_pointer.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo set address runtime in setup()
//     URL: https://github.com/RobTillaart/INA226
//
//  not tested with HW yet


#include "INA226.h"

INA226 X(0x40);
INA226 Y(0x41);

INA226 * INA;


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("INA226_LIB_VERSION: ");
  Serial.println(INA226_LIB_VERSION);
  Serial.println();

  INA = &X;
  Serial.println(INA->getAddress());
  INA = &Y;
  Serial.println(INA->getAddress());

  Wire.begin();
  INA->begin();

  INA->setMaxCurrentShunt(1, 0.002);
}


void loop()
{
  Serial.println("\nBUS\tSHUNT\tCURRENT\tPOWER");
  for (int i = 0; i < 20; i++)
  {
    Serial.print(INA->getBusVoltage(), 3);
    Serial.print("\t");
    Serial.print(INA->getShuntVoltage_mV(), 3);
    Serial.print("\t");
    Serial.print(INA->getCurrent_mA(), 3);
    Serial.print("\t");
    Serial.print(INA->getPower_mW(), 3);
    Serial.println();
    delay(1000);
  }
}


//  -- END OF FILE --
