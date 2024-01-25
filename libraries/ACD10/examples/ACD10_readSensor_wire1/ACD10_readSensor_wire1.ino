//
//    FILE: ACD10_readSensor.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/ACD10


#include "ACD10.h"


ACD10 mySensor(&Wire1);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ACD10_LIB_VERSION: ");
  Serial.println(ACD10_LIB_VERSION);

  Wire1.begin();
  mySensor.begin();
}


void loop()
{
  //  prepare a request every 5 seconds.
  if (millis() - mySensor.lastRead() > 5000)  //  millis
  {
    mySensor.requestSensor();
  }

  //  if request has had enough time read the sensor.
  if (mySensor.requestReady())
  {
    mySensor.readSensor();
    Serial.print(mySensor.getCO2Concentration());
    Serial.print("\t");
    Serial.print(mySensor.getTemperature());
    Serial.println();
  }

  //  do other things here.
  delay(1000);
}


//  -- END OF FILE --
