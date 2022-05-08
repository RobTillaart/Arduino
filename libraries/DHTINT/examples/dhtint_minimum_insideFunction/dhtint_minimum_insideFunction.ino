//
//    FILE: dhtint_minimum_insideFunction.ino
// AUTHORS: Rob Tillaart, Vladislaw Kuzmin
// PURPOSE: DHTINT library test sketch
//     URL: https://github.com/RobTillaart/DHTINT

// DHT PIN layout from left to right
// =================================
// FRONT : DESCRIPTION  
// pin 1 : VCC
// pin 2 : DATA
// pin 3 : Not Connected
// pin 4 : GND


#include <dhtint.h>

uint64_t previousMillis;


void setup()
{
  while(!Serial);        // MKR1010 needs this

  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();
}


void DHTt(uint8_t pin)
{
  DHTINT mySensor(pin);

  // MKR1010 needs this
  // mySensor.setDisableIRQ(false);

  if (millis() - mySensor.lastRead() > 2000)
  {
    previousMillis = millis();
    mySensor.read();
    Serial.print(mySensor.getHumidity());
    Serial.print("\t");
    Serial.println(mySensor.getTemperature());
  }
}


void loop()
{
  // call function...
  DHTt(2);
}


// -- END OF FILE --

