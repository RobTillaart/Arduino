//
//    FILE: ACD3100_readSensor.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/ACD3100


#include "ACD3100.h"


ACD3100 mySensor(&Wire);  //  explicit default, not needed.


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ACD3100_LIB_VERSION: ");
  Serial.println(ACD3100_LIB_VERSION);

  Wire.begin();
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
