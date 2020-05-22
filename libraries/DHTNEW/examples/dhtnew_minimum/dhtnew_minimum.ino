//
//    FILE: dhtnew_minimum.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: DHTNEW library test sketch for Arduino
//     URL: https://github.com/RobTillaart/DHTNew
// HISTORY:
// 0.1.0    2018-01-08 initial version
// 0.1.1    2020-04-30 replaced humidity and temperature with functions
//
// FRONT left 2 right
// pin 1 : VCC
// pin 2 : DATA
// pin 3 : NC
// PIN 4 : GND

#include <dhtnew.h>

DHTNEW mySensor(6);

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();

  mySensor.setHumOffset(10);
  mySensor.setTempOffset(-1.5);
}

void loop()
{
  if (millis() - mySensor.lastRead() > 2000)
  {
    mySensor.read();
    Serial.print(mySensor.getHumidity(), 1);
    Serial.print("\t");
    Serial.println(mySensor.getTemperature(), 1);
  }
}

// END OF FILE