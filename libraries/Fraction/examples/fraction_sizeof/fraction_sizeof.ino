//
//    FILE: fraction_sizeof.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test fraction memory
//     URL: https://github.com/RobTillaart/Fraction
//
//  On AVR it uses 10 bytes per element, where 8 were expected.
//

#include "fraction.h"


Fraction a(0.42);
Fraction arr[20];


void setup()
{
  Serial.begin(115200);
  Serial.print(__FILE__);
  Serial.print("FRACTION_LIB_VERSION: ");
  Serial.println(FRACTION_LIB_VERSION);
  Serial.println();

  arr[19] = a;

  Serial.println(a.toFloat());
  Serial.print("sizeof: \t");
  Serial.println(sizeof(a));
  Serial.println(arr[19].toFloat());
  Serial.print("sizeof: \t");
  Serial.println(sizeof(arr));
}


void loop()
{
}


//  -- END OF FILE --
