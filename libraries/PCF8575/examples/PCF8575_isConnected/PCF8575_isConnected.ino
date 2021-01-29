//
//    FILE: PCF8575_isConnected.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-03
//
// PUPROSE: demo 
//

#include "PCF8575.h"

// adjust addresses if needed
PCF8575 PCF(0x39);

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCF8575_LIB_VERSION:\t");
  Serial.println(PCF8575_LIB_VERSION);

  if (!PCF.begin())
  {
    Serial.println("could not initialize...");
  }
  if (!PCF.isConnected())
  {
    Serial.println("=> not connected");
  }
  else
  {
    Serial.println("=> connected!!");
  }
}

void loop()
{
}

// -- END OF FILE --
