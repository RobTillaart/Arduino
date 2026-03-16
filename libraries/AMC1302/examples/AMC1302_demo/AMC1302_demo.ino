//
//    FILE: AMC1302_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/AMC1302


#include "AMC1302.h"


AMC1302 amc(14, 15);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AMC1302_LIB_VERSION: ");
  Serial.println(AMC1302_LIB_VERSION);
  Serial.println();

  //  volts per step, shunt 50 milli-Ohm
  amc.begin(5.0/1023, 0.050);
}


void loop()
{
  Serial.print(amc.readCurrent(), 3);
  Serial.print("\t");
  Serial.print(amc.readVoltageN(), 3);
  Serial.print("\t");
  Serial.print(amc.readVoltageP(), 3);
  Serial.println();
  delay(1000);
}


//  -- END OF FILE --
