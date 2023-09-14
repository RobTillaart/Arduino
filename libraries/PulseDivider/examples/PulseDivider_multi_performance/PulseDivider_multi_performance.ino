//
//    FILE: PulseDivider_multi.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Test performance multi pulse dividers parallel
//    DATE: 2023-09-13
//     URL: https://github.com/RobTillaart/PulseDivider


#include "PulseDivider.h"

uint32_t start, duration;


void setup()
{
  Serial.begin(115200);

  Serial.print("PULSEDIVIDER_LIB_VERSION: ");
  Serial.println(PULSEDIVIDER_LIB_VERSION);
  delay(10);

  for (int i = 1; i < 11; i++)
  {
    test(i);
  }
}


void test(int n)
{
  PulseDivider PD(16, 17, 23, 13);
  PD.start();

  start = micros();
  uint32_t times = 10000UL * n;
  while (times-- > 0)
  {
    PD.check();
  }
  duration = micros() - start;

  Serial.println();
  Serial.print("TEST:\t");
  Serial.println(n);
  Serial.print("TIME:\t");
  Serial.println(duration * 0.0001);
  Serial.print("CPS:\t");
  Serial.println(uint32_t(1e10 / duration));
  delay(100);  //  flush printing
}


void loop()
{
}


//  -- END OF FILE --
