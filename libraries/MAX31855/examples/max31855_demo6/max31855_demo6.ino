//
//    FILE: max31855_demo6.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: thermocouple lib demo TCfactor
//    DATE: 2015-12-06
//     URL: http://forum.arduino.cc/index.php?topic=208061
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
  Serial.print("Start max31855_demo6: ");
  Serial.println(MAX31855_VERSION);
  Serial.println();

  tc.begin();
  tc.read();
  double t1 = tc.getTemperature();
  Serial.print("    temp before:\t");
  Serial.println(t1, 2);

  double tcf = tc.getTCfactor();
  Serial.print("TCfactor before:\t");
  Serial.println(tcf, 4);

  Serial.println("\nDefault adjust for J-type ThermoCouple");
  tc.setTCfactor(J_TC);
  tcf = tc.getTCfactor();
  Serial.print(" TCfactor after:\t");
  Serial.println(tcf, 4);

  tc.read();
  double t2 = tc.getTemperature();
  Serial.print("     temp after:\t");
  Serial.println(t2, 2);

  Serial.print("     temp delta:\t");
  Serial.println(abs(t1 - t2), 2);

  Serial.println("\ndone...");
}

void loop()
{
}
