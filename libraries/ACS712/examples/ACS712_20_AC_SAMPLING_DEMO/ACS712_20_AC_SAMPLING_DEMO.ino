//
//    FILE: ACS712_20_AC_SAMPLING_DEMO.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo to sample AC current and set mVPerAmpere
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
  float mA = ACS.mA_AC_sampling();
  Serial.println(mA, 1);

  while (Serial.available() > 0)
  {
    char c = Serial.read();

    if (c == '*') ACS.setmVperAmp(ACS.getmVperAmp() + 1);
    if (c == '/') ACS.setmVperAmp(ACS.getmVperAmp() - 1);
    Serial.print("mVperAmp:\t");
    Serial.println(ACS.getmVperAmp());
  }
  delay(250);
}


//  -- END OF FILE --
