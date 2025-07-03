//
//    FILE: print_fractions_denum_MT.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/printHelpers


#include "printHelpersMT.h"

uint32_t start, stop, duration;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PRINTHELPERS_LIB_VERSION: ");
  Serial.println(PRINTHELPERS_LIB_VERSION);
  Serial.println();

  delay(100);
  start = micros();
  char *p = fraction(PI, 65536);  //  2^16
  stop = micros();
  Serial.print("TIME: \t");
  Serial.println(stop - start);
  Serial.println(p);
  delay(100);

  start = micros();
  p = fraction(EULER, 65536);  //  2^16
  stop = micros();
  Serial.print("TIME: \t");
  Serial.println(stop - start);
  Serial.println(p);
  Serial.println();
  delay(100);

  //  notice most fractions will occur 3 or 4 times as denom
  //  is smaller than the step size of n.
  double n = 0.500;
  for (int i = 0; i <= 1000; i++)
  {
    Serial.print(i);
    Serial.print("\t");
    Serial.print(n, 3);
    Serial.print("\t");
    Serial.print(fraction(n, 256));
    Serial.println();
    n += 0.001;
  }
  Serial.println();

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
