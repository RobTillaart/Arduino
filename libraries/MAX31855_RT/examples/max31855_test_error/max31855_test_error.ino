//
//    FILE: max31855_test_error.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: thermocouple lib inline tests
//    DATE: 2019-07-31
//     URL: https://github.com/RobTillaart/MAX31855_RT
//

#include "MAX31855.h"

const int doPin = 7;
const int csPin = 6;
const int clPin = 5;

MAX31855 tc(clPin, csPin, doPin);

void setup() 
{
  Serial.begin(115200);
  Serial.print("Start max31855_test_error: ");
  Serial.println(MAX31855_VERSION);
  Serial.println();

  tc.begin();
}

void loop() 
{
  int status = tc.read();
  Serial.print("stat:\t\t");
  Serial.println(status);
  
  if (tc.getStatus())
  {
    Serial.print("error:\t\t");
    if (tc.shortToGND())   Serial.println("SHORT TO GROUND");
    if (tc.shortToVCC())   Serial.println("SHORT TO VCC");
    if (tc.openCircuit())  Serial.println("OPEN CIRCUIT");
    if (tc.genericError()) Serial.println("GENERIC ERROR");
    if (tc.noRead())       Serial.println("NO READ");
    if (tc.noCommunication()) Serial.println("NO COMMUNICATION");
  }

  float internal = tc.getInternal();
  Serial.print("internal:\t");
  Serial.println(internal, 3);

  float temp = tc.getTemperature();
  Serial.print("temperature:\t");
  Serial.println(temp, 2);
  delay(1000);
}

// -- END OF FILE --
