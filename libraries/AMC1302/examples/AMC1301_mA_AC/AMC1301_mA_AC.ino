//
//    FILE: AMC1301_mA_AC.ino
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
  amc.setFormFactor(AMC_FF_SINUS);
  //  adjust if needed
  amc.setMicrosAdjust(1.000);
  Serial.println(amc.detectFrequency());
  Serial.println(amc.getGain(), 1);
  delay(1000);
}


void loop()
{
  Serial.print(amc.mA_peak2peak(), 3);
  Serial.print("\t");
  Serial.print(amc.mA_AC(), 3);
  Serial.print("\t");
  Serial.print(amc.mA_AC_sampling(), 3);
  Serial.print("\t");
  Serial.println();
  delay(100);
}


//  -- END OF FILE --
