//
//    FILE: gammaTest.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/GAMMA

#include "gamma.h"


GAMMA gt1(256);
GAMMA gt2(128);
GAMMA gt3(64);
GAMMA gt4(32);    //  default
GAMMA gt5(16);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("GAMMA_LIB_VERSION: ");
  Serial.println(GAMMA_LIB_VERSION);

  gt1.begin();
  gt2.begin();
  gt3.begin();
  gt4.begin();
  gt5.begin();

  gt1.setGamma(2.8);
  gt2.setGamma(2.8);
  gt3.setGamma(2.8);
  gt4.setGamma(2.8);
  gt5.setGamma(2.8);

  for (int i = 0; i < 256; i++)
  {
    Serial.print(i);
    Serial.print('\t');
    Serial.print(gt1[i]);
    Serial.print('\t');
    Serial.print(gt2[i]);
    Serial.print('\t');
    Serial.print(gt3[i]);
    Serial.print('\t');
    Serial.print(gt4[i]);
    Serial.print('\t');
    Serial.print(gt5[i]);
    Serial.println();
  }

  Serial.println("\ndone...\n");
}


void loop()
{
}


//  -- END OF FILE --

