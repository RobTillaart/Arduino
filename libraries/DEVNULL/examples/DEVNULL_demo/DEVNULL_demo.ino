//
//    FILE: DEVNULL_demo.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2020-06-23
//    (c) : MIT
//

#include "DEVNULL.h"

DEVNULL dn;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

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


// -- END OF FILE --

