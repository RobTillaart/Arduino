//
//    FILE: max31855_demo6.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: thermocouple lib demo setSeebeckCoefficient()
//    DATE: 2015-12-06
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
  Serial.print("Start max31855_demo6: ");
  Serial.println(MAX31855_VERSION);
  Serial.println();

  tc.begin();
  tc.read();
  float t1 = tc.getTemperature();
  Serial.print("    temp before:\t");
  Serial.println(t1, 2);

  float tcf = tc.getSeebeckCoefficient();
  Serial.print("SeebeckCoefficient before:\t");
  Serial.println(tcf, 4);

  Serial.println("\nChange default K-type to J-type ThermoCouple");
  tc.setSeebeckCoefficient(J_TC);
  tcf = tc.getSeebeckCoefficient();
  Serial.print(" SeebeckCoefficient after:\t");
  Serial.println(tcf, 4);

  tc.read();
  float t2 = tc.getTemperature();
  Serial.print("     temp after:\t");
  Serial.println(t2, 2);

  Serial.print("     temp delta:\t");
  Serial.println(abs(t1 - t2), 2);

  Serial.println("\ndone...");
}

void loop()
{
}
