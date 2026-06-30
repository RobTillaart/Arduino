//
//    FILE: ACS712_20_PWM.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo to measure mA DC of a PWM signal
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
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ACS712_LIB_VERSION: ");
  Serial.println(ACS712_LIB_VERSION);
  Serial.println();

  ACS.autoMidPoint();
  //  Serial.println(ACS.getMidPoint());
}


void loop()
{
  //  100 mA threshold, 4 cycles.
  int mA = ACS.mA_DC_PWM(100, 4);
  Serial.println(mA);
  delay(1000);
}


//  -- END OF FILE --
