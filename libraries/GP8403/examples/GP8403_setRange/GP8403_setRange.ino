//
//    FILE: GP8403_setRange.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
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

  //  25 and 50% so voltages should be 2.5 and 5
  //             or 1.25 and 2.5
  myDAC.setPercentage(0, 50);
  myDAC.setPercentage(1, 25);
}


void loop()
{
  //  should give a sort of 1Hz square wave.
  myDAC.setRange(5);
  delay(1000);
  myDAC.setRange(10);
  delay(1000);
}


//  -- END OF FILE --
