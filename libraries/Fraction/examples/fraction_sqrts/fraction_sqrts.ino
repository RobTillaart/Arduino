//
//    FILE: fraction_sqrts.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: fraction version of first 10000 square roots
//     URL: https://github.com/RobTillaart/Fraction


#include "fraction.h"

Fraction sqr;


void setup()
{
  Serial.begin(115200);
  Serial.print(__FILE__);
  Serial.print("FRACTION_LIB_VERSION: ");
  Serial.println(FRACTION_LIB_VERSION);
  Serial.println();

  for ( int n = 0; n <= 10000; n++)
  {
    Fraction sqr( sqrt(n));
    float f = sqr.toFloat();
    //  test for relative error 1e-5
    //  if (abs((f * f / n) - 1) > 0.00001)
    {
      Serial.print(n);
      Serial.print("\t");
      Serial.print(sqr.toString());
      Serial.print("\t\t");
      Serial.print(sqrt(n), 7);
      Serial.print("\t\t");
      Serial.print(f, 7);
      Serial.print("\t\t");
      Serial.println(abs((f * f / n) - 1), 7);
    }
  }

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
