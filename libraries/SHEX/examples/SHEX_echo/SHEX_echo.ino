//
//    FILE: SHEX_echo.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo SHEX hexdump class
//    DATE: 2020-05-24
//    (c) : MIT
//

// this sketch echos all incoming bytes back in hex dump format.
// 

#include "SHEX.h"

// default Serial and length 16
SHEX shex;

// SHEX shex(&Serial, 8);

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
}

void loop()
{
  if (Serial.available())
  {
    char c = Serial.read();
    shex.print(c);
  }
}

// -- END OF FILE --
