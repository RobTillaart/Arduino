//
//    FILE: dhtnew_debug.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: DHTNEW library debug sketch for Arduino
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


void setup()
{
  Serial.begin(115200);
  Serial.println("dhtnew_debug.ino");
  Serial.print("DHTNEW_LIB_VERSION: ");
  Serial.println(DHTNEW_LIB_VERSION);
  Serial.println();

  //  MKR1010 needs this
  //  mySensor.setDisableIRQ(false);
}


void loop()
{
  delay(2000);
  mySensor.read();    //  put print statements in core lib (see read())
}


//  -- END OF FILE --

