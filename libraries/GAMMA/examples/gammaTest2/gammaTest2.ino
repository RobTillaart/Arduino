//
//    FILE: gamma_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo setGamma
//    DATE: 2020-08-08

// Use Arduino Plotter to see the different curves.

#include "gamma.h"

GAMMA gt;  // uses default 32 size

void setup()
{
  Serial.begin(115200);
  Serial.println("hello");
  for (int i = 0; i < 256; i++)
  {
    for (int gam = 1; gam < 10; gam += 1)
    {
      gt.setGamma(gam);
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
