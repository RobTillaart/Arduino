//
//    FILE: max31855_demo3.ino
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

  uint32_t start = micros();
  thermoCouple.read();
  uint32_t stop = micros();
  Serial.print("read:\t");
  Serial.println(stop - start);

  start = micros();
  float t1 = thermoCouple.getTemperature();
  stop = micros();
  Serial.print("getTemperature:\t");
  Serial.println(stop - start);

  start = micros();
  float t2 = thermoCouple.getInternal();
  stop = micros();
  Serial.print("getInternal:\t");
  Serial.println(stop - start);

  Serial.println();
  Serial.println(t1, 2);
  Serial.println(t2, 2);
  Serial.println();
}


void loop() 
{
  //  this loop returns multiples of about 73mSec (counter multiples of ~143)
  //  so the # measurements per second is about 14?
  uint32_t counter = 0;
  float t1 = thermoCouple.getTemperature();
  float t2 = t1;

  uint32_t start = micros();
  while (t2 == t1)
  {
    thermoCouple.read();
    t1 = thermoCouple.getTemperature();
    counter++;
  }
  uint32_t stop = micros();

  Serial.print("change:\t");
  Serial.println(stop - start);
  Serial.print("counter:\t");
  Serial.println(counter);
  Serial.println(t2, 2);
  Serial.println(t1, 2);
  Serial.println();
}


//  -- END OF FILE --

