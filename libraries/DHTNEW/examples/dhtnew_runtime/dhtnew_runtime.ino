//
//    FILE: dhtnew_runtime.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: DHTNEW library test sketch
//     URL: https://github.com/RobTillaart/DHTNew
//
// HISTORY:
// 0.1.0    2021-01-04  intial version
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

uint32_t lastTime = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println(DHTNEW_LIB_VERSION);
}

void loop()
{
  if (millis() - lastTime > 2000)
  {
    lastTime = millis();
    for (int pin = 6; pin < 10; pin++)
    {
      DHTNEW sensor(pin);
      sensor.read();
      Serial.print(pin);
      Serial.print("\t");
      Serial.print(sensor.getHumidity(), 1);
      Serial.print("\t");
      Serial.println(sensor.getTemperature(), 1);
    }
  }

  // Do other things here
}

// END OF FILE
