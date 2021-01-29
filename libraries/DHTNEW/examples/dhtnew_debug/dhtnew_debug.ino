//
//    FILE: dhtnew_debug.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: DHTNEW library debug sketch for Arduino
//     URL: https://github.com/RobTillaart/DHTNew
//
// HISTORY:
// 0.1.0    2020-12-15
//
// DHT PIN layout from left to right
// =================================
// FRONT : DESCRIPTION
// pin 1 : VCC
// pin 2 : DATA
// pin 3 : Not Connected
// pin 4 : GND

#include <dhtnew.h>

DHTNEW mySensor(6);

void setup()
{
  Serial.begin(115200);
  Serial.println("dhtnew_debug.ino");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHTNEW_LIB_VERSION);
  Serial.println();
}

void loop()
{
  delay(2000);
  mySensor.read();    // put print statements in core lib (see read())
}

// END OF FILE
