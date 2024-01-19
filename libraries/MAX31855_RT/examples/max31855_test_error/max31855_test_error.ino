//
//    FILE: max31855_test_error.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.0
// PURPOSE: thermocouple lib inline tests
//    DATE: 2019-07-31
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

  if (thermoCouple.getStatus())
  {
    Serial.print("error:\t\t");
    if (thermoCouple.shortToGND())   Serial.println("SHORT TO GROUND");
    if (thermoCouple.shortToVCC())   Serial.println("SHORT TO VCC");
    if (thermoCouple.openCircuit())  Serial.println("OPEN CIRCUIT");
    if (thermoCouple.genericError()) Serial.println("GENERIC ERROR");
    if (thermoCouple.noRead())       Serial.println("NO READ");
    if (thermoCouple.noCommunication()) Serial.println("NO COMMUNICATION");
  }

  float internal = thermoCouple.getInternal();
  Serial.print("internal:\t");
  Serial.println(internal, 3);

  float temp = thermoCouple.getTemperature();
  Serial.print("temperature:\t");
  Serial.println(temp, 2);
  delay(1000);
}


//  -- END OF FILE --

