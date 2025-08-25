//
//    FILE: SHEX_echo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo SHEX hex dump class
//     URL: https://github.com/RobTillaart/SHEX
//
//  this sketch echoes all incoming bytes back in hex dump format.
//


#include "SHEX.h"

//  default Serial and length 16
SHEX shex;

//  SHEX shex(&Serial, 8);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SHEX_LIB_VERSION: ");
  Serial.println(SHEX_LIB_VERSION);
  Serial.println();
}


void loop()
{
  if (Serial.available())
  {
    char c = Serial.read();
    shex.print(c);
  }
}


//  -- END OF FILE --

