//    FILE: ansi_deviceType.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/ANSI/issues/9

//  NOT TESTED
//  - with real terminal
//  - with dummies

#include "ansi.h"


ANSI ansi(&Serial);
int deviceType = -1;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
}


void loop()
{
  if (deviceType == -1)
  {
    deviceType = ansi.deviceType(100);
    Serial.print("DEV_TYPE: ");
    Serial.println(deviceType);
  }
  delay(1000);
}


//  -- END OF FILE --
