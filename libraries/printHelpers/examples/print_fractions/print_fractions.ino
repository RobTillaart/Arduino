//
//    FILE: print_fractions.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/printHelpers


#include "printHelpers.h"

uint32_t start, stop, duration;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PRINTHELPERS_LIB_VERSION: ");
  Serial.println(PRINTHELPERS_LIB_VERSION);
  Serial.println();

  delay(100);
  start = micros();
  char *p = fraction(-PI);
  stop = micros();
  Serial.print("TIME: \t");
  Serial.println(stop - start);
  Serial.println(p);
  delay(100);

  double n = 0.500;
  for (int i = 0; i <= 1000; i++)
  {
    Serial.print(i);
    Serial.print("\t");
    Serial.print(n, 3);
    Serial.print("\t");
    Serial.print(fraction(n));
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
