//
//    FILE: INA3221_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo polling 3 channels
//     URL: https://github.com/RobTillaart/INA3221_RT


#include "INA3221.h"


INA3221 INA(0x40);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("INA3221_LIB_VERSION: ");
  Serial.println(INA3221_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (!INA.begin() )
  {
    Serial.println("could not connect. Fix and Reboot");
  }
  else
  {
    Serial.print("Found: \t");
    Serial.println(INA.getAddress());
  }

  Serial.print("DieID: \t");
  Serial.println(INA.getDieID(), HEX);
  Serial.print("ManID: \t");
  Serial.println(INA.getManufacturerID(), HEX);
  Serial.print(" Conf: \t");
  Serial.println(INA.getConfiguration(), HEX);

  //  overwrite default shunts.
  INA.setShuntR(0, 0.100);
  INA.setShuntR(1, 0.102);
  INA.setShuntR(2, 0.099);

  Serial.println("\nCHAN\tCRITIC\tWARNING");
  for (int ch = 0; ch < 3; ch++)
  {
    Serial.print(ch);
    Serial.print("\t");
    Serial.print(INA.getCriticalAlert(ch), HEX);
    Serial.print("\t");
    Serial.print(INA.getWarningAlert(ch), HEX);
    Serial.println();
  }

  Serial.println("\nShunt Voltage");
  Serial.print("  SVSUM:\t");
  Serial.println(INA.getShuntVoltageSum(), HEX);
  Serial.print("SVLIMIT:\t");
  Serial.println(INA.getShuntVoltageSumLimit(), HEX);

  Serial.println("\nMask/ Enable");
  Serial.print("M/E:\t");
  Serial.println(INA.getMaskEnable(), HEX);

  Serial.println("\nPower Limit");
  Serial.print("UPPER:\t");
  Serial.println(INA.getPowerUpperLimit(), HEX);
  Serial.print("LOWER:\t");
  Serial.println(INA.getPowerLowerLimit(), HEX);




}


void loop()
{
  Serial.println("\nCHAN\tBUS\tSHUNT\tCURRENT\tPOWER");
  for (int ch = 0; ch < 3; ch++)
  {
    Serial.print(ch);
    Serial.print("\t");
    Serial.print(INA.getBusVoltage(ch), 3);
    Serial.print("\t");
    Serial.print(INA.getShuntVoltage_mV(ch), 3);
    Serial.print("\t");
    Serial.print(INA.getCurrent_mA(ch), 3);
    Serial.print("\t");
    Serial.print(INA.getPower_mW(ch), 3);
    Serial.println();
    delay(1000);
  }
}


//  -- END OF FILE --
