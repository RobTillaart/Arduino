//
//    FILE: const.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2021-11-15
// PURPOSE: test complex math - https://github.com/RobTillaart/Complex/issues/7
//     URL: https://github.com/RobTillaart/Complex


#include "Complex.h"


void setup()
{
  Serial.begin(115200);
  Serial.print(__FILE__);
  Serial.print("\n  COMPLEX_LIB_VERSION: ");
  Serial.println(COMPLEX_LIB_VERSION);

  const Complex unity(1, 0);
  Complex a(1,1);
  Complex b(2,2);
  Complex c = unity * a + b; 

  Serial.println(a);
  Serial.println(b);
  Serial.println(c);

  const Complex d(1,1);
  //  The next line is a warning on AVR 
  //  But an error on other platforms (which is correct)
  //  d *= b;
  Serial.println(d);

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --

