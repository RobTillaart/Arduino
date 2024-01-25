//
//    FILE: ACS712_20_AC_DEMO.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo to set the mVperAmpere and Form FActor.
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
  Serial.print("ACS712_LIB_VERSION: ");
  Serial.println(ACS712_LIB_VERSION);

  ACS.autoMidPoint();
}


void loop()
{
  int mA = ACS.mA_AC();
  Serial.println(mA);

  if (Serial.available() > 0)
  {
    char c = Serial.read();

    if (c == '*') ACS.setmVperAmp(ACS.getmVperAmp() + 1);
    if (c == '/') ACS.setmVperAmp(ACS.getmVperAmp() - 1);
    Serial.print("mVperAmp:\t");
    Serial.println(ACS.getmVperAmp());

    if (c == '+') ACS.setFormFactor(ACS.getFormFactor() * 1.05);
    if (c == '-') ACS.setFormFactor(ACS.getFormFactor() / 1.05);
    Serial.print("formFactor:\t");
    Serial.println(ACS.getFormFactor());
  }
  delay(1000);
}


//  -- END OF FILE --

