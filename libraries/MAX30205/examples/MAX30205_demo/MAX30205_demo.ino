//
//    FILE: MAX30205_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/MAX30205


#include "MAX30205.h"


MAX30205 mySensor(0x40);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MAX30205_LIB_VERSION: ");
  Serial.println(MAX30205_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (mySensor.begin() == false)
  {
    Serial.print("Could not find sensor at ");
    Serial.println(mySensor.getAddress());
    while(1);
  }
}


void loop()
{
  if (millis() - mySensor.lastRead() < 1000)
  {
    mySensor.read();
    Serial.println(mySensor.getTemperature());
  }

  delay(1000);
}


//  -- END OF FILE --
