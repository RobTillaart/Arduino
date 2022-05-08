//
//    FILE: dhtint_minimum.ino
//  AUTHOR: Rob Tillaart
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
// #include <dhtnew.h>

DHTINT mySensor(5);   // ESP 16    UNO 5    MKR1010 5


void setup()
{
  while(!Serial);        // MKR1010 needs this

  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();

  // MKR1010 needs this
  // mySensor.setDisableIRQ(false);

  Serial.println("BEFORE OFFSET");
  mySensor.read();
  Serial.print(mySensor.getHumidity());
  Serial.print("\t");
  Serial.println(mySensor.getTemperature());

  mySensor.setHumOffset(10);
  mySensor.setTempOffset(-3);

  Serial.println("AFTER OFFSET");
}


void loop()
{
  if (millis() - mySensor.lastRead() > 2000)
  {
    mySensor.read();
    Serial.print(mySensor.getHumidity());
    Serial.print("\t");
    Serial.println(mySensor.getTemperature());
  }
}


// -- END OF FILE --
