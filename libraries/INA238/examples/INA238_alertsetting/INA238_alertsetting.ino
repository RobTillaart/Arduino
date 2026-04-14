//
//    FILE: INA238_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo core functions
//     URL: https://github.com/RobTillaart/INA238


#include "INA238.h"


INA238 INA(0x40);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("INA238_LIB_VERSION: ");
  Serial.println(INA238_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (!INA.begin() )
  {
    Serial.println("Could not connect. Fix and Reboot");
    while(1);
  }

  INA.setADCRange(1);
  INA.setMaxCurrentShunt(10, 0.015);
  INA.setShuntVoltageConversionTime(INA238_150_us);
  INA.setAverage(INA238_16_SAMPLES); 
  INA.setOverCurrentLimit(2750); // in mA
  INA.setDiagnoseAlertBit(INA238_DIAG_ALERT_LATCH); //Set to Alert latch
}


void loop()
{
  Serial.println("\nVBUS\tVSHUNT\tCURRENT\tPOWER\tTEMP");
  for (int i = 0; i < 20; i++)
  {
    Serial.print(INA.getBusVoltage(), 3);
    Serial.print("\t");
    Serial.print(INA.getShuntMilliVolt(), 3);
    Serial.print("\t");
    Serial.print(INA.getMilliAmpere(), 3);
    Serial.print("\t");
    Serial.print(INA.getMilliWatt(), 3);
    Serial.print("\t");
    Serial.print(INA.getTemperature(), 3);
    Serial.println();
    delay(1000);
  }
}


//  -- END OF FILE --
