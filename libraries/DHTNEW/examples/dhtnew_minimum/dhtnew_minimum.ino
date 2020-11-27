//
//    FILE: dhtnew_minimum.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: DHTNEW library test sketch
//     URL: https://github.com/RobTillaart/DHTNew
//
// HISTORY:
// 0.1.0    2018-01-08 initial version
// 0.1.1    2020-04-30 replaced humidity and temperature with functions
// 0.1.2    2020-06-15 match 0.3.0 error handling
//
// DHT PIN layout from left to right
// =================================
// FRONT : DESCRIPTION  
// pin 1 : VCC
// pin 2 : DATA
// pin 3 : Not Connected
// pin 4 : GND

#include <dhtnew.h>

DHTNEW mySensor(16);

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();

  Serial.println("BEFORE OFFSET");
  mySensor.read();
  Serial.print(mySensor.getHumidity(), 1);
  Serial.print("\t");
  Serial.println(mySensor.getTemperature(), 1);

  mySensor.setHumOffset(10);
  mySensor.setTempOffset(-3.5);

  Serial.println("AFTER OFFSET");
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
