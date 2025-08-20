//
//    FILE: DEVNULL_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/DEVNULL


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

  dn.println("it is dark in here...");

  if (dn.available())
  {
    int c = dn.read();
    Serial.println(c);
  }

  Serial.println("Done...");
}


void loop()
{
}


//  -- END OF FILE --

