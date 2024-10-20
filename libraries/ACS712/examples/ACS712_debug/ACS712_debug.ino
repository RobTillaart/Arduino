//
//    FILE: ACS712_debug.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: analyse effects of settings e.g. voltage divider
//     URL: https://github.com/RobTillaart/ACS712


#include "ACS712.h"


//  Arduino UNO has 5.0 volt with a max ADC value of 1023 steps
//  ACS712 5A  uses 185 mV per A
//  ACS712 20A uses 100 mV per A
//  ACS712 30A uses  66 mV per A


ACS712  ACS(A0, 3.3, 1023, 185);
ACS712  ACS2(A0, 1, 1023, 32);
ACS712  ACS3(A0, 3.3, 1023, 37);
ACS712  ACS4(A0, 1, 1023, 92.5);
//  ESP 32 example (might requires resistors to step down the logic voltage)
//  ACS712  ACS(25, 3.3, 4095, 185);


float voltageDividerFactor(float R_ACS, float R_GND)
{
  return R_GND / (R_ACS + R_GND);
}


void dumpACS(ACS712 acs)
{
  Serial.print("MIDPOINT: ");
  Serial.println(acs.getMidPoint());
  Serial.print("NOISE mV: ");
  Serial.println(acs.getNoisemV());
  Serial.print("mV / AMP: ");
  Serial.println(acs.getmVperAmp());
  Serial.print("mA/step : ");
  Serial.println(acs.getmAPerStep());
  Serial.println();
}


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("ACS712_LIB_VERSION: ");
  Serial.println(ACS712_LIB_VERSION);

  dumpACS(ACS);
  dumpACS(ACS2);
  dumpACS(ACS3);
  dumpACS(ACS4);

  //  just examples
  Serial.println(voltageDividerFactor(300, 75), 4);
  Serial.println(voltageDividerFactor(315, 70), 4);
}


void loop()
{
}


//  -- END OF FILE --
