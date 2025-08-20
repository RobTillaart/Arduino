//
//    FILE: dhtnew_minimum_insideFunction.ino
// AUTHORS: Rob Tillaart, Vladislaw Kuzmin
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

uint64_t previousMillis;


void setup()
{
  while(!Serial);        //  MKR1010 needs this

  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHTNEW_LIB_VERSION);
  Serial.println();
}


void DHTt(uint8_t pin)
{
  DHTNEW mySensor(pin);

  //  MKR1010 needs this
  //  mySensor.setDisableIRQ(false);

  if (millis() - mySensor.lastRead() > 2000)
  {
    previousMillis = millis();
    mySensor.read();
    Serial.print(mySensor.getHumidity(), 2);
    Serial.print("\t");
    Serial.println(mySensor.getTemperature(), 2);
  }
}


void loop()
{
  DHTt(2);
}


//  -- END OF FILE --

