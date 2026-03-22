//
//    FILE: AMC1301_mA_DC.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/AMC1302
//
//  To be tested with hardware


#include "AMC1302.h"


AMC1301 amc(14, 15);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AMC1302_LIB_VERSION: ");
  Serial.println(AMC1302_LIB_VERSION);
  Serial.println();

  //  volts per step, shunt 50 milli-Ohm
  amc.begin(5.0 / 1023, 0.050);
  //  should print 8.2
  //  Serial.println(amc.getGain(), 1);
}


void loop()
{
  Serial.print(amc.mA_DC(), 3);
  Serial.println();
  delay(1000);
}


//  -- END OF FILE --
