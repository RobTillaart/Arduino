//
//    FILE: DEVNULL_lastByte.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/DEVNULL
//
//  expected output
//  -1
//  33  !


#include "DEVNULL.h"

DEVNULL dn;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DEVNULL_LIB_VERSION: ");
  Serial.println(DEVNULL_LIB_VERSION);
  Serial.println();


  Serial.println(dn.lastByte());
  dn.print("Hello!");

  Serial.print(dn.lastByte());
  Serial.print('\t');
  Serial.println(char(dn.lastByte()));

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
