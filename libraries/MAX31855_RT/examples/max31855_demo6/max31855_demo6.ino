//
//    FILE: max31855_demo6.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: thermocouple lib demo setSeebeckCoefficient()
//    DATE: 2015-12-06
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

  thermoCouple.read();
  float t1 = thermoCouple.getTemperature();
  Serial.print("    temp before:\t");
  Serial.println(t1, 2);

  float tcf = thermoCouple.getSeebeckCoefficient();
  Serial.print("SeebeckCoefficient before:\t");
  Serial.println(tcf, 4);

  Serial.println("\nChange default K-type to J-type ThermoCouple");
  thermoCouple.setSeebeckCoefficient(J_TC);
  tcf = thermoCouple.getSeebeckCoefficient();
  Serial.print(" SeebeckCoefficient after:\t");
  Serial.println(tcf, 4);

  thermoCouple.read();
  float t2 = thermoCouple.getTemperature();
  Serial.print("     temp after:\t");
  Serial.println(t2, 2);

  Serial.print("     temp delta:\t");
  Serial.println(abs(t1 - t2), 2);

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --

