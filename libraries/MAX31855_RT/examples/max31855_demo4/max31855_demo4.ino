//
//    FILE: max31855_demo4.ino
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
  for (int i = 0; i < 10; i++) thermoCouple.read();
  uint32_t stop = micros();
  Serial.print("10x read:\t");
  Serial.println(stop - start);


  start = micros();
  float t1 = thermoCouple.getTemperature();
  stop = micros();
  Serial.print("getTemperature:\t");
  Serial.println(stop - start);
  Serial.println(t1, 2);
  Serial.println();

  start = micros();
  thermoCouple.setOffset(2.0);
  stop = micros();
  Serial.print("setOffset:\t");
  Serial.println(stop - start);

  start = micros();
  thermoCouple.getOffset();
  stop = micros();
  Serial.print("getOffset:\t");
  Serial.println(stop - start);

  thermoCouple.read();
  start = micros();
  t1 = thermoCouple.getTemperature();
  stop = micros();
  Serial.print("getTemperature:\t");
  Serial.println(stop - start);
  Serial.println(t1, 2);
  Serial.println();


  start = micros();
  float t2 = thermoCouple.getInternal();
  stop = micros();
  Serial.print("getInternal:\t");
  Serial.println(stop - start);
  Serial.println(t2, 4);
  Serial.println();
}


void loop()
{
}


//  -- END OF FILE --

