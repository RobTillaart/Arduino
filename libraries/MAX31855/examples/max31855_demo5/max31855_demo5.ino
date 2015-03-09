//
//    FILE: max31855_demo5.ino
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
  Serial.print("Start max31855_demo5: ");
  Serial.println(MAX31855_VERSION);
  Serial.println();

  tc.begin();
  tc.read();
  double t1 = tc.getTemperature();
  Serial.print("  temp before:\t");
  Serial.println(t1, 2);

  double o = tc.getOffset();
  Serial.print("offset before:\t");
  Serial.println(o, 2);

  tc.setOffset(3.14);
  o = tc.getOffset();
  Serial.print(" offset after:\t");
  Serial.println(o, 2);

  tc.read();
  double t2 = tc.getTemperature();
  Serial.print("   temp after:\t");
  Serial.println(t1, 2);

  Serial.print("   temp delta:\t");
  Serial.println(abs(t1 - t2), 2);

  Serial.println("\ndone...");
}

void loop() 
{
}





