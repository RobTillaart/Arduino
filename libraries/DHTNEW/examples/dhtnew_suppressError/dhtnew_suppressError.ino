//
//    FILE: dhtnew_suppressError.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: DHTNEW library test sketch
//     URL: https://github.com/RobTillaart/DHTNew
//
// HISTORY:
// 0.1.0    2020-07-17 initial version
//
// DHT PIN layout from left to right
// =================================
// FRONT : DESCRIPTION
// pin 1 : VCC
// pin 2 : DATA
// pin 3 : Not Connected
// pin 4 : GND


// run sketch without connected sensor to see effect

#include <dhtnew.h>

DHTNEW mySensor(16);

uint32_t count = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();

  // test flag working => prints 010
  Serial.print(mySensor.getSuppressError());
  mySensor.setSuppressError(true);
  Serial.print(mySensor.getSuppressError());
  mySensor.setSuppressError(false);
  Serial.print(mySensor.getSuppressError());

  // change to false to see difference
  mySensor.setSuppressError(true);
  Serial.println();
}

void loop()
{
  if (millis() - mySensor.lastRead() > 2000)
  {
    if ((count % 10) == 0) Serial.println("\nERR\tHUM\tTEMP");
    count++;

    int errcode = mySensor.read();
    Serial.print(errcode);
    Serial.print("\t");
    Serial.print(mySensor.getHumidity(), 1);
    Serial.print("\t");
    Serial.println(mySensor.getTemperature(), 1);
  }
}

// -- END OF FILE --