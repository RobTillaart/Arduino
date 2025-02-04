//
//    FILE: ACD3100_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/ACD3100


#include "ACD3100.h"


ACD3100 mySensor;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ACD3100_LIB_VERSION: ");
  Serial.println(ACD3100_LIB_VERSION);

  Wire.begin();
  mySensor.begin();
  while (!mySensor.preHeatDone())
  {
    delay(10000);
    Serial.print("..");
    Serial.println(mySensor.preHeatMillisLeft() / 1000);
  }
  Serial.println();
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
