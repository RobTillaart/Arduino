//
//    FILE: MAX30205_comparator_fan.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/MAX30205
//
//  Connect OS output to a FAN (indirect via transistor or so)
//  Technically it is possible to have an array of sensors and
//  start another fan for every 2 degrees temperature rise.
//  And swith them off gradually of course.

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
    while (1);  //  block!
  }

  //  set FAN on level
  mySensor.setOverTemperature(30);
  //  set FAN off level
  mySensor.setHysteresis(25);
  //  invert polarity (optional, depends on hardware used)
  mySensor.setPolarity(HIGH);
  //  start comparator mode
  mySensor.setModeComparator();
}


void loop()
{
  if (millis() - mySensor.lastRead() < 60000UL)
  {
    mySensor.read();
    Serial.println(mySensor.getTemperature());
  }

  delay(1000);
}


//  -- END OF FILE --
