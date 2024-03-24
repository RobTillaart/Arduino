//
//    FILE: dhtnew_runtime.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: DHTNEW library test sketch
//     URL: https://github.com/RobTillaart/DHTNew

//  DHT PIN layout from left to right
//  =================================
//  FRONT : DESCRIPTION
//  pin 1 : VCC
//  pin 2 : DATA
//  pin 3 : Not Connected
//  pin 4 : GND


#include <dhtnew.h>

DHTNEW mySensor(5);   //  ESP 16    UNO 5    MKR1010 5

uint32_t lastTime = 0;


void setup()
{
  while(!Serial);     //  MKR1010 needs this

  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DHTNEW_LIB_VERSION: ");
  Serial.println(DHTNEW_LIB_VERSION);

  //  MKR1010 needs this
  //  mySensor.setDisableIRQ(false);

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

  //  Do other things here
}


//  -- END OF FILE --

