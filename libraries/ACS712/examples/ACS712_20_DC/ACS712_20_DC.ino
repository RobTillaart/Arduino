//
//    FILE: ACS712_20_DC.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2020-03-18
//    (c) : MIT
//

#include "ACS712.h"

// Arduino UNO has 5.0 volt with a max ADC value of 1023 steps
// ACS712 5A  uses 185 mV per A
// ACS712 20A uses 100 mV per A
// ACS712 30A uses  66 mV per A

ACS712  ACS(A0, 5.0, 1023, 100);
// ESP 32 example (requires resistors to step down the logic voltage)
//ACS712  ACS(25, 5.0, 4095, 185);

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  ACS.autoMidPoint();
}

void loop()
{
  int mA = ACS.mA_DC();
  Serial.println(mA);
}

// END OF FILE
