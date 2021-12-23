//
//    FILE: pressure_specific.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-11-26
//     URL: https://github.com/RobTillaart/pressure


#include "pressure.h"


pressure P;

uint32_t start, stop;
float x;

volatile float value = 1.234;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PRESSURE_LIB_VERSION: ");
  Serial.println(PRESSURE_LIB_VERSION);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    P.setPSI(value);
    x = P.getMSW();
  }
  stop = micros();
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  Serial.print("MSW:\t");
  Serial.println(x);
  delay(10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = PSI2MSW(value);
  }
  stop = micros();
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  Serial.print("MSW:\t");
  Serial.println(x);
  delay(10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = value * (PSI2MILLIBAR * MILLIBAR2MSW);
  }
  stop = micros();
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  Serial.print("MSW:\t");
  Serial.println(x);
  delay(10);

}

void loop()
{
}

inline float PSI2MSW(float value)
{
  return value * (PSI2MILLIBAR * MILLIBAR2MSW);
}


// -- END OF FILE --

