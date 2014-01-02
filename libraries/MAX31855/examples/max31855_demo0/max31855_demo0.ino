//
//    FILE: max31855_demo.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
// PURPOSE: thermocouple lib demo application
//    DATE: 2014-01-01
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
}

void loop() 
{
  int status = tc.read();
  Serial.print("stat:\t\t");
  Serial.println(status);

  float internal = tc.getInternal();
  Serial.print("internal:\t");
  Serial.println(internal);

  float temp = tc.getTemperature();
  Serial.print("temperature:\t");
  Serial.println(temp);
  delay(1000);
}


