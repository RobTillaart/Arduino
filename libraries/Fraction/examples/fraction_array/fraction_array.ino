//
//    FILE: fraction_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test fraction memory
//     URL: https://github.com/RobTillaart/Fraction
//
//  (0.1.16) On AVR it uses 10 bytes per element, where 8 were expected.
//  (0.2.0)  solved this 


#include "fraction.h"


Fraction arr[50];


void setup()
{
  Serial.begin(115200);
  Serial.print(__FILE__);
  Serial.print("FRACTION_LIB_VERSION: ");
  Serial.println(FRACTION_LIB_VERSION);
  Serial.println();

  for ( int n = 0; n < 33; n++)
  {
    arr[n] = Fraction(n, 32);
    Serial.print(n);
    Serial.print("\t");
    Serial.print(arr[n].toString());
    Serial.print("\t");
    Serial.print(arr[n].toFloat(), 7);
    Serial.print("\t");
    Serial.println(n / 32.0, 7);
  }

  Serial.println("\ndone...");
}


void loop()
{
}

//  -- END OF FILE --
