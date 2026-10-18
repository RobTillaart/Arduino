//
//    FILE: INA239_voltage_divider.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo setVoltageRatio()
//     URL: https://github.com/RobTillaart/INA239


#include "INA239.h"

//  select, dataIn, dataOut, clock == SOFTWARE SPI
//  INA239 INA(5, 6, 7, 8);

//  select, &SPI === HW SPI
INA239 INA(5, &SPI);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("INA239_LIB_VERSION: ");
  Serial.println(INA239_LIB_VERSION);
  Serial.println();

  SPI.begin();

  if (!INA.begin() )
  {
    Serial.println("Could not connect. Fix and Reboot");
    while (1);
  }

  INA.setVoltageRatio(1.5f);
  Serial.println(INA.getVoltageRatio());
  INA.setBusVoltageLSB();
  Serial.println(INA.getBusVoltageLSB(), 6);
  INA.setMaxCurrentShunt(10, 0.015);
}


void loop()
{
  //  use factory default LSB
  INA.setVoltageRatio(1.0f);
  Serial.println("\nVBUS\tPOWER raw");
  for (int i = 0; i < 5; i++)
  {
    Serial.print(INA.getBusVoltage(), 3);
    Serial.print("\t");
    Serial.print(INA.getMilliWatt(), 3);
    Serial.println();
    delay(1000);
  }

  //  use corrected LSB
  //  example map 120 Volt to 80 Volt
  //  ratio = 120/80 = 1.5, keeping 5 Volt marg
  INA.setVoltageRatio(1.5f);
  Serial.println("\nVBUS\tPOWER corrected");
  for (int i = 0; i < 5; i++)
  {
    Serial.print(INA.getBusVoltage(), 3);
    Serial.print("\t");
    Serial.print(INA.getMilliWatt(), 3);
    Serial.println();
    delay(1000);
  }
}


//  -- END OF FILE --
