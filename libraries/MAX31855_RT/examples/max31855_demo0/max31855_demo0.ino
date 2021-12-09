//
//    FILE: max31855_demo0.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: thermocouple lib demo application
//    DATE: 2014-01-01
//     URL: https://github.com/RobTillaart/MAX31855_RT
//


#include "MAX31855.h"


const int doPin = 7;
const int csPin = 6;
const int clPin = 5;


MAX31855 tc;


void setup() 
{
  Serial.begin(115200);
  Serial.print("Start max31855_demo0: ");
  Serial.println(MAX31855_VERSION);
  Serial.println();

  tc.begin(clPin, csPin, doPin);
}


void loop() 
{
  int status = tc.read();
  Serial.print("stat:\t\t");
  Serial.println(status);

  float internal = tc.getInternal();
  Serial.print("internal:\t");
  Serial.println(internal, 3);

  float temp = tc.getTemperature();
  Serial.print("temperature:\t");
  Serial.println(temp, 3);
  delay(1000);
}


// -- END OF FILE

