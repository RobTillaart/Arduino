//
//    FILE: dhtint_suppressError.ino
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


// run sketch without connected sensor to see effect


#include <dhtint.h>

DHTINT mySensor(5);   // ESP 16    UNO 5    MKR1010 5

uint32_t count = 0;


void setup()
{
  while(!Serial);        // MKR1010 needs this

  Serial.begin(115200);
  Serial.println("dhtint_suppressError");
  Serial.print("DHTINT_LIB_VERSION: ");
  Serial.println(DHTINT_LIB_VERSION);
  Serial.println();

  // MKR1010 needs this
  // mySensor.setDisableIRQ(false);

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

