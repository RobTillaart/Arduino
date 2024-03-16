//
//    FILE: INA219_get_settings.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: check reading / writing configuration.
//     URL: https://github.com/RobTillaart/INA219


#include "INA219.h"

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

  Serial.println();

  ///////////////////////////////////////////////

  Serial.print("CALI:\t");
  Serial.println(INA.isCalibrated());
  Serial.print("CLSB:\t");
  Serial.println(INA.getCurrentLSB());
  Serial.print("SHUNT:\t");
  Serial.println(INA.getShunt(), 4);
  Serial.print("MAXC:\t");
  Serial.println(INA.getMaxCurrent(), 4);

  INA.setMaxCurrentShunt(5, 0.002);    //  adjust if needed.

  Serial.println();

  Serial.print("CALI:\t");
  Serial.println(INA.isCalibrated());
  Serial.print("CLSB:\t");
  Serial.println(INA.getCurrentLSB());
  Serial.print("SHUNT:\t");
  Serial.println(INA.getShunt(), 4);
  Serial.print("MAXC:\t");
  Serial.println(INA.getMaxCurrent(), 4);

  Serial.println();

  ///////////////////////////////////////////////

  Serial.print("BVR:\t");
  INA.setBusVoltageRange(16);
  Serial.print(INA.getBusVoltageRange());

  Serial.print("\t");
  INA.setBusVoltageRange(32);
  Serial.print(INA.getBusVoltageRange());

  Serial.println();

  ///////////////////////////////////////////////

  Serial.print("GAIN:\t");
  INA.setGain(1);
  Serial.print(INA.getGain());

  Serial.print("\t");
  INA.setGain(2);
  Serial.print(INA.getGain());

  Serial.print("\t");
  INA.setGain(4);
  Serial.print(INA.getGain());

  Serial.print("\t");
  INA.setGain(8);
  Serial.print(INA.getGain());

  Serial.println();

  ///////////////////////////////////////////////

  Serial.print("BADC:\t");
  for (uint8_t b = 0; b < 16; b++)
  {
    INA.setBusADC(b);
    Serial.print(INA.getBusADC());
    Serial.print("\t");
  }
  INA.setBusADC(3);
  Serial.println();

  ///////////////////////////////////////////////

  Serial.print("SADC:\t");
  for (uint8_t s = 0; s < 16; s++)
  {
    INA.setShuntADC(s);
    Serial.print(INA.getShuntADC());
    Serial.print("\t");
  }
  INA.setShuntADC(3);
  Serial.println();

  ///////////////////////////////////////////////

  Serial.print("MODE:\t");
  for (uint8_t m = 0; m < 8; m++)
  {
    INA.setMode(m);
    Serial.print(INA.getMode());
    Serial.print("\t");
  }
  INA.setMode(7);
  Serial.println();

  ///////////////////////////////////////////////

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
