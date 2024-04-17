//
//    FILE: INA3221_tests.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test functions read/write values (crude unit test).
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


  Serial.println("\nSHUNT0\tSHUNT1\tSHUNT2 (Ohm)");
  for (int ch = 0; ch < 3; ch++)
  {
    Serial.print(INA.getShuntR(ch), 4);
    Serial.print("\t");
  }
  Serial.println();

  //  overwrite default shunts.
  INA.setShuntR(0, 0.100);
  INA.setShuntR(1, 0.102);
  INA.setShuntR(2, 0.099);

  for (int ch = 0; ch < 3; ch++)
  {
    Serial.print(INA.getShuntR(ch), 4);
    Serial.print("\t");
  }
  Serial.println();


  Serial.println("\nCHAN\tCRITIC\tWARNING\t (uV)");
  for (int ch = 0; ch < 3; ch++)
  {
    Serial.print(ch);
    Serial.print("\t");
    Serial.print(INA.getCriticalAlert(ch));
    Serial.print("\t");
    Serial.print(INA.getWarningAlert(ch));
    Serial.println();
  }
  //  overwrite default Alerts
  INA.setCriticalAlert(0, 50000);
  INA.setCriticalAlert(1, 100000);
  INA.setCriticalAlert(2, 150000);
  INA.setWarningAlert(0, 25000);
  INA.setWarningAlert(1, 75000);
  INA.setWarningAlert(2, 125000);

  Serial.println("\nCHAN\tCRITIC\tWARNING\t (uV)");
  for (int ch = 0; ch < 3; ch++)
  {
    Serial.print(ch);
    Serial.print("\t");
    Serial.print(INA.getCriticalAlert(ch));
    Serial.print("\t");
    Serial.print(INA.getWarningAlert(ch));
    Serial.println();
  }

  Serial.println("\nShunt Voltage (uV)");
  Serial.print("  SVSUM:\t");
  Serial.println(INA.getShuntVoltageSum());
  Serial.print("SVLIMIT:\t");
  Serial.println(INA.getShuntVoltageSumLimit());

  INA.setShuntVoltageSumLimit(32198);
  Serial.print("SVLIMIT:\t");
  Serial.println(INA.getShuntVoltageSumLimit());

  Serial.println("\nMask/ Enable");
  Serial.print("M/E:\t");
  Serial.println(INA.getMaskEnable(), HEX);


  Serial.println("\nPower Limit");
  Serial.print("UPPER:\t");
  Serial.println(INA.getPowerUpperLimit());
  Serial.print("LOWER:\t");
  Serial.println(INA.getPowerLowerLimit());

  INA.setPowerUpperLimit(5000);
  INA.setPowerLowerLimit(4000);

  Serial.print("UPPER:\t");
  Serial.println(INA.getPowerUpperLimit());
  Serial.print("LOWER:\t");
  Serial.println(INA.getPowerLowerLimit());


  Serial.println("\ngetEnableChannel");
  for (int ch = 0; ch < 3; ch++)
  {
    Serial.print(INA.getEnableChannel(ch));
    Serial.print("\t");
  }
  Serial.println();
  Serial.println("Disable Channel");
  for (int ch = 0; ch < 3; ch++)
  {
    INA.disableChannel(ch);
    Serial.print(INA.getEnableChannel(ch));
    Serial.print("\t");
  }
  Serial.println();
  Serial.println("Enable Channel");
  for (int ch = 0; ch < 3; ch++)
  {
    INA.enableChannel(ch);
    Serial.print(INA.getEnableChannel(ch));
    Serial.print("\t");
  }
  Serial.println();


  Serial.println("\nAverage");
  for (int avg = 0; avg < 8; avg++)
  {
    INA.setAverage(avg);
    Serial.print(INA.getAverage());
    Serial.print("\t");
  }
  Serial.println();
  INA.setAverage(0);


  Serial.println("\nBusVoltageConversionTime");
  for (int bvct = 0; bvct < 8; bvct++)
  {
    INA.setBusVoltageConversionTime(bvct);
    Serial.print(INA.getBusVoltageConversionTime());
    Serial.print("\t");
  }
  Serial.println();
  INA.setBusVoltageConversionTime(0);


  Serial.println("\nShuntVoltageConversionTime");
  for (int svct = 0; svct < 8; svct++)
  {
    INA.setShuntVoltageConversionTime(svct);
    Serial.print(INA.getShuntVoltageConversionTime());
    Serial.print("\t");
  }
  Serial.println();
  INA.setShuntVoltageConversionTime(0);
}


void loop()
{
}


//  -- END OF FILE --
