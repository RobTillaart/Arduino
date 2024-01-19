//
//    FILE: max31855_demo0.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: thermocouple lib demo application
//    DATE: 2014-01-01
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
}


void loop() 
{
  int status = thermoCouple.read();
  Serial.print("stat:\t\t");
  Serial.println(status);

  float internal = thermoCouple.getInternal();
  Serial.print("internal:\t");
  Serial.println(internal, 3);

  float temp = thermoCouple.getTemperature();
  Serial.print("temperature:\t");
  Serial.println(temp, 3);
  delay(1000);
}


//  -- END OF FILE
