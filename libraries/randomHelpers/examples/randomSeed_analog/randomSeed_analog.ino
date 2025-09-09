//    FILE: randomSeed_analog.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: random seed generation with analogRead()
//     URL: https://github.com/RobTillaart/randomHelpers
//
//    NOTE: analogRead() is not a good source of entropy for the seed


#include "Arduino.h"

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  //  Serial.print("RANDOM_HELPERS_VERSION: ");
  //  Serial.println(RANDOM_HELPERS_VERSION);
  Serial.println();
  delay(100);

  //  use the last 32 bits of noise
  uint32_t zd = 0;
  start = micros();
  for (int i = 0; i < 32; i++)
  {
    zd <<= 1;
    zd ^= analogRead(A0);
  }
  stop = micros();
  Serial.print("SEED:\t");
  Serial.println(zd, HEX);
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  Serial.println();
}


void loop()
{
  //  use the last 32 bits of noise
  uint32_t zd = 0;
  for (int i = 0; i < 32; i++)
  {
    zd <<= 1;
    zd ^= analogRead(A0);
    delay(1);
  }
  Serial.println(zd);
}


//  -- END OF FILE --
