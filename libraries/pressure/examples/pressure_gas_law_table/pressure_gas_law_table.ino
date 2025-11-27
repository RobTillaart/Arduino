//
//    FILE: pressure_gas_law_table.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: create table for effect temperature - ideal gas law
//     URL: https://github.com/RobTillaart/pressure


#include "pressure.h"


pressure P;

float pressure = 1019.1;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PRESSURE_LIB_VERSION: ");
  Serial.println(PRESSURE_LIB_VERSION);
  Serial.println();

  for (int t = 25; t <= 100; t++)
  {
    Serial.print(t);
    Serial.print("\t");
    Serial.print(1019.1);
    Serial.print("\t");
    Serial.println(1019.1 * P.factorTemperatureKelvin(25, t), 3);
  }
  
  Serial.println("\ndone...");

}

void loop()
{
}


//  -- END OF FILE --
