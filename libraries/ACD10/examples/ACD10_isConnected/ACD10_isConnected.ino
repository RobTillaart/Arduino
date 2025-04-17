//
//    FILE: ACD10_isConnected.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/ACD10


#include "ACD10.h"


ACD10 mySensor;


void setup()
{
  //  while(!Serial);  //  uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ACD10_LIB_VERSION: ");
  Serial.println(ACD10_LIB_VERSION);
  Serial.println();

  Wire.begin();
  mySensor.begin();
}


void loop()
{
  Serial.println(mySensor.isConnected());
  Serial.println(mySensor.getAddress());
  delay(1000);
}


//  -- END OF FILE --
