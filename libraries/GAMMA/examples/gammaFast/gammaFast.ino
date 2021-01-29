//
//    FILE: gamma_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2020-08-08


#include "gamma.h"

GAMMA gt1(256);

// fastGamma is based upon values found with GAMMA(8).setGamma(2.8);
// it is however not that fast...

int fastGamma(uint8_t idx)
{
  if (idx <  32) return map(idx,   0,  31, 0, 1);
  if (idx <  64) return map(idx,  32,  63, 1, 5);
  if (idx <  96) return map(idx,  64,  31, 5, 17);
  if (idx < 128) return map(idx,  96, 127, 17, 37);
  if (idx < 160) return map(idx, 128, 159, 37, 69);
  if (idx < 192) return map(idx, 160, 191, 69, 115);
  if (idx < 224) return map(idx, 192, 223, 115, 177);
  return map(idx, 224, 255, 177, 255);
}


void setup()
{
  Serial.begin(115200);

  gt1.setGamma(2.8);

  for (int i = 0; i < 256; i++)
  {
    Serial.print(i);
    Serial.print('\t');
    Serial.print(gt1[i]);
    Serial.print('\t');
    Serial.print(fastGamma(i));  
    Serial.println();
  }

  volatile int x;
  uint32_t start = micros();
  for (int i = 0; i < 256; i++) x += gt1[i];
  uint32_t d1 = micros() - start;
  Serial.println(d1);
  delay(10);

  start = micros();
  for (int i = 0; i < 256; i++) x += fastGamma(i);
  d1 = micros() - start;
  Serial.println(d1);
  delay(10);

  Serial.println(x);
}


void loop()
{
}

// -- END OF FILE --
