//
//    FILE: max31855_demo1.ino
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
}


void loop() 
{
  int status = thermoCouple.read();
  if (status != 0)
  {
    Serial.print("stat:\t\t");
    Serial.println(status);
  }

  float temp = thermoCouple.getTemperature();
  int m = temp * 10 - 200;

  Serial.print(temp);
  Serial.print('\t');
  for (int i = 0; i < m; i++) Serial.write(']');
  Serial.println();
}


//  -- END OF FILE --

