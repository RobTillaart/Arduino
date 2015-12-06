//
//    FILE: max31855_demo3.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.03
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
  Serial.print("Start max31855_demo3: ");
  Serial.println(MAX31855_VERSION);
  Serial.println();

  tc.begin();

  uint32_t start = micros();
  tc.read();
  uint32_t stop = micros();
  Serial.print("read:\t");
  Serial.println(stop - start);

  start = micros();
  double t1 = tc.getTemperature();
  stop = micros();
  Serial.print("getTemperature:\t");
  Serial.println(stop - start);

  start = micros();
  tc.getInternal();
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
  // this loop returns multiples of about 73mSec (counter multiples of ~143)
  // so the # measurements per second is about 14?
  uint32_t counter = 0;
  double t1 = tc.getTemperature();
  double t2 = t1;

  uint32_t start = micros();
  while (t2 == t1)
  {
    tc.read();
    t1 = tc.getTemperature();
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
 