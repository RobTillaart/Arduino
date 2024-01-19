//
//    FILE: max31855_demo5.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: thermocouple lib demo application
//    DATE: 2014-01-02
//     URL: https://github.com/RobTillaart/MAX31855_RT
//


#include "MAX31855.h"


const int selectPin = 7;
const int dataPin   = 6;
const int clockPin  = 5;

MAX31855 thermoCouple(selectPin, dataPin, clockPin);


void setup() 
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAX31855_VERSION : ");
  Serial.println(MAX31855_VERSION);
  Serial.println();
  delay(250);

  SPI.begin();

  thermoCouple.begin();

  thermoCouple.read();
  float t1 = thermoCouple.getTemperature();
  Serial.print("  temp before:\t");
  Serial.println(t1, 2);

  float offset = thermoCouple.getOffset();
  Serial.print("offset before:\t");
  Serial.println(offset, 2);

  thermoCouple.setOffset(3.14);
  offset = thermoCouple.getOffset();
  Serial.print(" offset after:\t");
  Serial.println(offset, 2);

  thermoCouple.read();
  float t2 = thermoCouple.getTemperature();
  Serial.print("   temp after:\t");
  Serial.println(t2, 2);

  Serial.print("   temp delta:\t");
  Serial.println(abs(t1 - t2), 2);

  Serial.println("\ndone...");
}


void loop() 
{
}


//  -- END OF FILE --

