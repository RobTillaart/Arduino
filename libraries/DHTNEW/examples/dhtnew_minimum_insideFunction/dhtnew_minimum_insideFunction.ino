//
//    FILE: dhtnew_minimum_insideFunction.ino
// AUTHORS: Rob Tillaart, Vladislaw Kuzmin
// VERSION: 0.1.2
// PURPOSE: DHTNEW library test sketch
//     URL: https://github.com/RobTillaart/DHTNew
//
// HISTORY:
// 0.1.5    2021-02-19 improved the sketch to read DHT value in a function
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

uint64_t previousMillis;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();
}


void DHTt(uint8_t pin)
{
  DHTNEW mySensor(pin);
  
  if (millis() - mySensor.lastRead() > 2000)
  {
    previousMillis = millis();
    mySensor.read();
    Serial.print(mySensor.getHumidity(), 2);
    Serial.print("\t");
    Serial.println(mySensor.getTemperature(), 2);
  }
}


void loop() {
  DHTt(2);
}

// END OF FILE
