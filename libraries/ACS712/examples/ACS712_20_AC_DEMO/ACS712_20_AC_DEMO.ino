//
//    FILE: ACS712_20_AC_DEMO.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: demo to set midpoint and mVperAmpere for class.
//    DATE: 2020-03-18
//    (c) : MIT
//

#include "ACS712.h"

// Arduino UNO has 5.0 volt with a max ADC value of 1023 steps
// ACS712 5A  uses 185 mV per A
// ACS712 20A uses 100 mV per A
// ACS712 30A uses  66 mV per A

ACS712  ACS(A0, 5.0, 1023, 100);

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
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

// END OF FILE