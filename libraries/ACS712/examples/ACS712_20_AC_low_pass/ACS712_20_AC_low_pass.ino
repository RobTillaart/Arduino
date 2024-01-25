//
//    FILE: ACS712_20_AC_low_pass.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo AC measurement with point to point with low pass filter
//     URL: https://github.com/RobTillaart/ACS712


#include "ACS712.h"


//  Arduino UNO has 5.0 volt with a max ADC value of 1023 steps
//  ACS712 5A  uses 185 mV per A
//  ACS712 20A uses 100 mV per A
//  ACS712 30A uses  66 mV per A


ACS712  ACS(A0, 5.0, 1023, 185);
//  ESP 32 example (might requires resistors to step down the logic voltage)
//  ACS712  ACS(25, 3.3, 4095, 185);

float value  = 0;
float weight = 0.2;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("ACS712_LIB_VERSION: ");
  Serial.println(ACS712_LIB_VERSION);

  ACS.autoMidPoint();

  Serial.print("MidPoint: ");
  Serial.println(ACS.getMidPoint());
  Serial.print("Noise mV: ");
  Serial.println(ACS.getNoisemV());
  Serial.print("Amp/Step: ");
  Serial.println(ACS.getAmperePerStep(), 4);

  value = ACS.mA_AC();             //  get good initial value
}


void loop()
{
  //  select appropriate function
  float mA = ACS.mA_AC_sampling();
  //  float mA = ACS.mA_AC();
  value += weight * (mA - value);  //  low pass filtering

  Serial.print("weight: ");
  Serial.print(weight);
  Serial.print(" value: ");
  Serial.print(value, 0);
  Serial.print(" mA: ");
  Serial.print(mA);
  Serial.println();

  delay(1000);
}


//  -- END OF FILE --
