//
//    FILE: ACS712_20_AC_midPoint_compare.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo to compare different midPoint methods.
//     URL: https://github.com/RobTillaart/ACS712


#include "ACS712.h"


//  Arduino UNO has 5.0 volt with a max ADC value of 1023 steps
//  ACS712 5A  uses 185 mV per A
//  ACS712 20A uses 100 mV per A
//  ACS712 30A uses  66 mV per A


ACS712  ACS(A0, 5.0, 1023, 100);
//  ESP 32 example (might requires resistors to step down the logic voltage)
//  ACS712  ACS(25, 3.3, 4095, 185);


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.println();
  Serial.print("ACS712_LIB_VERSION: ");
  Serial.println(ACS712_LIB_VERSION);

  Serial.println("Compare different midPoint methods.\n");

  Serial.print("Default: \t");
  Serial.println(ACS.getMidPoint());

  Serial.print("AutoMP: \t");
  Serial.println(ACS.autoMidPoint());

  uint16_t average = (ACS.getMinimum(20) + ACS.getMaximum(20)) / 2;
  ACS.setMidPoint(average);
  Serial.print("Average: \t");
  Serial.println(average);
  Serial.println();
  Serial.println("\ndone...");
}


void loop()
{
  delay(1000);
}


//  -- END OF FILE --
