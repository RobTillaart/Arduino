//
//    FILE: HC4052_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for HC4052 2 x 4 channel (simple) multiplexer
//     URL: https://github.com/RobTillaart/HC4052


#include "HC4052.h"

HC4052 mp(4, 5, 6);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HC4052_LIB_VERSION: ");
  Serial.println(HC4052_LIB_VERSION);
  Serial.println();
  delay(100);

  mp.setChannel(3);

  Serial.println("400x different channel");
  delay(100);
  start = micros();
  for (int i = 0; i < 100; i++)
  {
    for (uint8_t channel = 0; channel < 4; channel++)
    {
      mp.setChannel(channel);
    }
  }
  stop = micros();
  Serial.print("TIME diff: ");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println((stop - start) / 400.0);
  delay(100);

  Serial.println("400x same channel");
  delay(100);
  start = micros();
  for (int i = 0; i < 100; i++)
  {
    for (uint8_t channel = 0; channel < 4; channel++)
    {
      mp.setChannel(2);
    }
  }
  stop = micros();
  Serial.print("TIME same: ");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println((stop - start) / 400.0);
  delay(100);
}


void loop()
{
}


//  -- END OF FILE --
