//
//    FILE: max31855_demo4.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: thermocouple lib demo application
//    DATE: 2014-01-02
//     URL:
//
// Released to the public domain
//

#include "MAX31855.h"

const int doPin = 7;
const int csPin = 6;
const int clPin = 5;

MAX31855 tc(clPin, csPin, doPin);

void setup() 
{
  Serial.begin(115200);
  Serial.print("Start max31855_demo4: ");
  Serial.println(MAX31855_VERSION);
  Serial.println();

  tc.begin();

  uint32_t start = micros();
  for (int i=0; i< 10; i++) tc.read();
  uint32_t stop = micros();
  Serial.print("10x read:\t");
  Serial.println(stop - start);


  start = micros();
  float t1 = tc.getTemperature();
  stop = micros();
  Serial.print("getTemperature:\t");
  Serial.println(stop - start);
  Serial.println(t1, 2);
  Serial.println();


  start = micros();
  tc.setOffset(2.0);
  stop = micros();
  Serial.print("setOffset:\t");
  Serial.println(stop - start);

  tc.read();
  start = micros();
  t1 = tc.getTemperature();
  stop = micros();
  Serial.print("getTemperature:\t");
  Serial.println(stop - start);
  Serial.println(t1, 2);
  Serial.println();


  start = micros();
  float t2 = tc.getInternal();
  stop = micros();
  Serial.print("getInternal:\t");
  Serial.println(stop - start);
  Serial.println(t2, 4);
  Serial.println();
}

void loop() 
{
}








