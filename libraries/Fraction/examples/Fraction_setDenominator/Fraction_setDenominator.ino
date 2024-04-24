//
//    FILE: Fraction_setDenominator.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Calculate fraction with well chosen number.
//     URL: https://github.com/RobTillaart/Fraction


#include "fraction.h"


void setup()
{
  Serial.begin(115200);
  Serial.print(__FILE__);
  Serial.println();
  Serial.println();

  Fraction pi(PI);
  Fraction appr = Fraction::setDenominator(pi, 32);
  Serial.println(pi.toString());
  Serial.println(pi.toDouble(), 10);
  Serial.println(appr.toString());
  Serial.println(appr.toDouble(), 10);
  Serial.println();

  Fraction ee(EULER);
  appr = Fraction::setDenominator(ee, 32);
  Serial.println(ee.toString());
  Serial.println(ee.toDouble(), 10);
  Serial.println(appr.toString());
  Serial.println(appr.toDouble(), 10);
  Serial.println();

  Fraction tt(0.125);
  appr = Fraction::setDenominator(tt, 32);
  Serial.println(tt.toString());
  Serial.println(tt.toDouble(), 10);
  Serial.println(appr.toString());
  Serial.println(appr.toDouble(), 10);
  Serial.println();

  Serial.println("done...\n");
}


void loop()
{
}


//  -- END OF FILE --
