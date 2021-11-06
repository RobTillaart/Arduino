//
//    FILE: Kelvin2RGB_timing.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: demo - shows timing 2 methods
//    DATE: 2020-07-29
//     URL: https://github.com/RobTillaart/Kelvin2RGB
//


#include "Kelvin2RGB.h"

Kelvin2RGB KRGB;

uint32_t start, stop, duration1, duration2;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  KRGB.begin();

  test_timing();
  
  Serial.println("\ndone...");
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
  duration1 = stop - start;

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    KRGB.convert_NB(temp, bright);
  }
  stop = micros();
  duration2 = stop - start;

  Serial.print("TH:\t");
  Serial.println(duration1 * 0.001);
  Serial.print("NB:\t");
  Serial.println(duration2 * 0.001);
  Serial.print("ratio:\t");
  Serial.println(1.0 * duration1 / duration2, 4);
}


// -- END OF FILE --

