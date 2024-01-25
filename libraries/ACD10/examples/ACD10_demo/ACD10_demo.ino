//
//    FILE: ACD10_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/ACD10


#include "ACD10.h"


ACD10 mySensor;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ACD10_LIB_VERSION: ");
  Serial.println(ACD10_LIB_VERSION);

  Wire.begin();
  mySensor.begin();
}


void loop()
{
  mySensor.requestSensor();
  while (mySensor.requestReady() == false) delay(10);
  mySensor.readSensor();
  Serial.print(mySensor.getCO2Concentration());
  Serial.print("\t");
  Serial.print(mySensor.getTemperature());
  Serial.println();

  delay(2000);
}


//  -- END OF FILE --
