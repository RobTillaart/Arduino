//
//    FILE: gammaTest2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo setGamma
//    DATE: 2020-08-08

// Use Arduino Plotter to see the different curves.


#include "gamma.h"

GAMMA gt;  // uses default 32 size


void setup()
{
  Serial.begin(115200);
  Serial.println("gammaTest2.ino");

  gt.begin();

  for (int i = 0; i < 256; i++)
  {
    for (float gamma = 0.1; gamma < 10; gamma *= 2)
    {
      gt.setGamma(gamma);
      Serial.print(gt[i]);
      Serial.print('\t');
    }
    Serial.println();
  }
}


void loop()
{
}


// -- END OF FILE --

