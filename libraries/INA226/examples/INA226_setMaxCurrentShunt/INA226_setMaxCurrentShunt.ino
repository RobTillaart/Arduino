//
//    FILE: INA226_setMaxCurrentShunt.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-06-22
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
  Serial.println();
  delay(100);


  INA.setMaxCurrentShunt(1, 0.002);
  Serial.println("normalized = true (default)");
  printConfig();

  INA.setMaxCurrentShunt(1, 0.002, false);
  Serial.println("normalized = false");
  printConfig();


  INA.setMaxCurrentShunt(15, 0.002);
  Serial.println("normalized = true (default)");
  printConfig();

  INA.setMaxCurrentShunt(15, 0.002, false);
  Serial.println("normalized = false");
  printConfig();
}


void loop()
{
  INA.setMaxCurrentShunt(1, 0.002);
  measure(20);

  INA.setMaxCurrentShunt(1, 0.002, false);
  measure(20);
}


void measure(uint8_t count)
{
  // delay(3000);
  Serial.println("\nBUS\tSHUNT\tCURRENT\tPOWER");
  Serial.println(" V\t mV\t mA\t mW");
  for (int i = 0; i < count; i++)
  {
    Serial.print(INA.getBusVoltage(), 3);
    Serial.print("\t");
    Serial.print(INA.getShuntVoltage_mV(), 3);
    Serial.print("\t");
    Serial.print(INA.getCurrent_mA(), 3);
    Serial.print("\t");
    Serial.print(INA.getPower_mW(), 3);
    Serial.println();
    delay(500);
  }
}


void printConfig()
{
  Serial.print("LSB:\t");
  Serial.println(INA.getCurrentLSB(), 10);
  Serial.print("LSB_uA:\t");
  Serial.println(INA.getCurrentLSB_uA(), 3);
  Serial.print("shunt:\t");
  Serial.println(INA.getShunt(), 3);
  Serial.print("maxCur:\t");
  Serial.println(INA.getMaxCurrent(), 3);
  Serial.println();
}


// -- END OF FILE --

