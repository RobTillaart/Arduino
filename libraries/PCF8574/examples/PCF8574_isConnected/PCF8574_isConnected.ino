//
//    FILE: PCF8574_isConnected.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-03
// PURPOSE: demo isConnected function
//     URL: https://github.com/RobTillaart/PCF8574


#include "PCF8574.h"

//  adjust addresses if needed
PCF8574 PCF_39(0x39);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCF8574_LIB_VERSION:\t");
  Serial.println(PCF8574_LIB_VERSION);

  Wire.begin();

  if (!PCF_39.begin())
  {
    Serial.println("could not initialize...");
  }
  if (!PCF_39.isConnected())
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


//  -- END OF FILE --

