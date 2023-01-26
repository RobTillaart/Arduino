//
//    FILE: gammaFast.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo


#include "gamma.h"


GAMMA gt1(256);

//  fastGamma is based upon values found with GAMMA(8).setGamma(2.8);
//  it is however not fast enough...
//  binary search
int fastGamma(uint8_t idx)
{
  if (idx < 128)
  {
    if (idx <  64)
    {
      if (idx <  32) return map(idx,   0,  31, 0, 1);
      return map(idx,  32,  63, 1, 5);
    }
    else
    {
      if (idx <  96) return map(idx,  64,  95, 5, 17);
      return map(idx,  96, 127, 17, 37);
    }
  }
  if (idx < 192)
  {
    if (idx < 160) return map(idx, 128, 159, 37, 69);
    return map(idx, 160, 191, 69, 115);
  }
  if (idx < 224) return map(idx, 192, 223, 115, 177);
  return map(idx, 224, 255, 177, 255);
}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("GAMMA_LIB_VERSION: ");
  Serial.println(GAMMA_LIB_VERSION);

  gt1.begin();
  gt1.setGamma(2.8);

  Serial.println("\n\ttest fastGamma()");
  Serial.println("\ti \tgt1[] \tfast \tdelta");
  for (int i = 0; i < 256; i ++ )
  {
    Serial.print('\t');
    Serial.print(i);
    Serial.print('\t');
    Serial.print(gt1[i]);
    Serial.print('\t');
    Serial.print(fastGamma(i));
    Serial.print('\t');
    Serial.print(gt1[i] - fastGamma(i));
    Serial.println();
  }

  volatile uint32_t x = 0;
  uint32_t start = micros();
  for (int i = 0; i < 256; i++) x += gt1[i];
  uint32_t d1 = micros() - start;
  Serial.println();
  Serial.print(" 256 x gt1[i] : ");
  Serial.println(d1);
  Serial.print("            x : ");
  Serial.println(x);
  delay(10);

  x = 0;
  start = micros();
  for (int i = 0; i < 256; i++) x += fastGamma(i);
  d1 = micros() - start;
  Serial.print(" 256 x fast   : ");
  Serial.println(d1);
  Serial.print("            x : ");
  Serial.println(x);
  delay(10);

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
