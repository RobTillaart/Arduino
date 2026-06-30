//
//    FILE: GP8403_percentage.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/GP8403


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
  //  follow potmeter
  float percentage = analogRead(A0) * 0.1;
  myDAC.setPercentage(0, percentage);
}


//  -- END OF FILE --
