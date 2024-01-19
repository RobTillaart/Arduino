//
//    FILE: max31855_demo2.ino
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


float t1, t2;

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
  t1 = thermoCouple.getTemperature();
  delay(1000);
}


void loop()
{
  thermoCouple.read();
  t2 = thermoCouple.getTemperature();
  Serial.print("delta:\t");
  Serial.println(t2 - t1, 2);
  t1 = t2;
  delay(1000);
}


//  -- END OF FILE --

