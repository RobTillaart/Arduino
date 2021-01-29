//
//    FILE: Kelvin2RGB_timing.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo - shows timing 2 methods
//    DATE: 2020-07-29
//     URL: https://github.com/RobTillaart/Kelvin2RGB
//


#include "Kelvin2RGB.h"

Kelvin2RGB KRGB;

uint32_t start, stop, d1, d2;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  KRGB.begin();

  test_timing();
}

void loop()
{
}

void test_timing()
{
  Serial.println(__FUNCTION__);
  Serial.println();

  // volatile to minimize optimization
  volatile float bright = 100.0;
  volatile float temp   = 6500.0;

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    KRGB.convert_TH(temp, bright);
  }
  stop = micros();
  d1 = stop - start;

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    KRGB.convert_NB(temp, bright);
  }
  stop = micros();
  d2 = stop - start;

  Serial.print("TH:\t");
  Serial.println(d1 * 0.001);
  Serial.print("NB:\t");
  Serial.println(d2 * 0.001);
  Serial.print("ratio:\t");
  Serial.println(1.0 * d1 / d2, 4);
}

// -- END OF FILE --
