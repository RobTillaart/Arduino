//
//    FILE: pressure_gas_law.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo ideal gas law
//    DATE: 2021-12-23
//     URL: https://github.com/RobTillaart/pressure


#include "pressure.h"


pressure P;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PRESSURE_LIB_VERSION: ");
  Serial.println(PRESSURE_LIB_VERSION);
  Serial.println();

  P.setMilliBar(1019.1);
  P.changeTemperature(273.15 + 25, 273.15 + 50);
  Serial.print(1019.1);
  Serial.print(" heated from 25 to 50C gives ");
  Serial.println(P.getMilliBar());

  P.setMilliBar(1019.1);
  P.changeVolume(2, 1);
  Serial.print(1019.1);
  Serial.print(" with volume in half gives ");
  Serial.println(P.getMilliBar());

  P.setMilliBar(1019.1);
  P.changeMole(2, 4);
  Serial.print(1019.1);
  Serial.print(" with atoms doubled gives ");
  Serial.println(P.getMilliBar());

  Serial.println();
  P.setMilliBar(1019.1);
  P.change(273.15 + 25, 273.15 + 50, 2, 1, 2, 4);
  Serial.print(1019.1);
  Serial.print(" with all above gives ");
  Serial.println(P.getMilliBar());

  P.setMilliBar(1019.1);
  P.changeTemperature(273.15 + 25, 273.15 + 50);
  P.changeVolume(2, 1);
  P.changeMole(2, 4);
  Serial.print(1019.1);
  Serial.print(" check the last one: ");
  Serial.println(P.getMilliBar());
}

void loop()
{
}


// -- END OF FILE --
