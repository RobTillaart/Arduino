//
//    FILE: ACS712_20_AC_midPoint_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo to compare different midPoint methods.
//     URL: https://github.com/RobTillaart/ACS712


#include "ACS712.h"


//  Arduino UNO has 5.0 volt with a max ADC value of 1023 steps
//  ACS712 5A  uses 185 mV per A
//  ACS712 20A uses 100 mV per A
//  ACS712 30A uses  66 mV per A


ACS712  ACS(A0, 5.0, 1023, 100);
//  ESP 32 example (might requires resistors to step down the logic voltage)
//  ACS712  ACS(25, 3.3, 4095, 185);

uint32_t start, stop;

float mp = 0;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.println();
  Serial.print("ACS712_LIB_VERSION: ");
  Serial.println(ACS712_LIB_VERSION);

  Serial.println("Compare different midPoint methods.\n");

  start = micros();
  mp = ACS.getMidPoint();
  stop = micros();
  Serial.print("Default: \t");
  Serial.print(mp);
  Serial.print("\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  mp = ACS.autoMidPoint();
  stop = micros();
  Serial.print("AutoMP: \t");
  Serial.print(mp);
  Serial.print("\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  uint16_t average = (ACS.getMinimum(20) + ACS.getMaximum(20)) / 2;
  stop = micros();
  Serial.print("Average: \t");
  Serial.print(average);
  Serial.print("\t");
  Serial.println(stop - start);
  delay(10);

  Serial.println("\ndone...");
}


void loop()
{
  delay(1000);
}


//  -- END OF FILE --
