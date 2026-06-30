//
//    FILE: GP8403_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/GP8403

#include "Arduino.h"
#include "Wire.h"
#include "GP8403.h"


GP8403 myDAC(0x40, &Wire);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("GP8403_LIB_VERSION: ");
  Serial.println(GP8403_LIB_VERSION);
  Serial.println();

  Wire.begin();
  myDAC.begin();
}


void loop()
{
  //  sawtooth 0 = rising
  //  sawtooth 1 = falling
  for (int i = 0; i < 4095; i++)
  {
    myDAC.setValue(0, i);
    myDAC.setValue(1, 4095 - i);
    delay(1);
  }
  delay(2000);
}


//  -- END OF FILE --
