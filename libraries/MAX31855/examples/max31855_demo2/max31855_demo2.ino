//
//    FILE: max31855_demo2.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
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
  Serial.print("Start max31855_demo: ");
  Serial.println(MAX31855_VERSION);
  Serial.println();

  tc.begin();
  tc.read();
}

void loop() 
{
  float t1 = tc.getTemperature();
  delay(1000);
  tc.read();
  float t2 = tc.getTemperature();
  Serial.print("delta:\t");
  Serial.println(t2-t1, 2);
  delay(1000);
}



