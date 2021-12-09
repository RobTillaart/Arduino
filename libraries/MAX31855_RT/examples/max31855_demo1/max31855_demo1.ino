//
//    FILE: max31855_demo1.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.0
// PURPOSE: thermocouple lib demo application
//    DATE: 2014-01-02
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
  Serial.print("Start max31855_demo1: ");
  Serial.println(MAX31855_VERSION);
  Serial.println();

  tc.begin(clPin, csPin, doPin);
}


void loop() 
{
  int status = tc.read();
  if (status != 0)
  {
    Serial.print("stat:\t\t");
    Serial.println(status);
  }

  float temp = tc.getTemperature();
  int m = temp * 10 - 200;

  Serial.print(temp);
  Serial.print('\t');
  for (int i = 0; i < m; i++) Serial.write(']');
  Serial.println();
}


// -- END OF FILE --

