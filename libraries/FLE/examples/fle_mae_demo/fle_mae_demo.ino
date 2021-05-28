//
//    FILE: fle_mae_demo.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2020-07-21
//     URL: https://github.com/RobTillaart/FLE


#include "FLE.h"

FLE ar[20];


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();

  // simulate measurement with errors
  for (int i = 0; i < 20; i++)
  {
    ar[i] = FLE(9.0 + random(200) * 0.01, random(100) * 0.001);
    Serial.println(ar[i]);
  }

  Serial.println("----------------------------");
  Serial.println(meanAverageError(ar, 20, 2));
  Serial.println("----------------------------");
  Serial.println(meanError(ar, 20, 3));
  Serial.println("\nDone...");
}


void loop()
{
}


FLE meanAverageError(FLE *, uint8_t len, uint8_t dec)
{
  if (len == 0) return FLE(0, 0);
  float a = 0;
  float b = 0;
  for (uint8_t i = 0; i < len; i++)
  {
    a += ar[i].value();
    b += ar[i].error();
  }
  FLE x(a / len, b / len);
  x.setDecimals(dec);
  return x;
}


FLE meanError(FLE *, uint8_t len, uint8_t dec)
{
  if (len == 0) return FLE(0, 0);
  float a = 0;
  float h = ar[0].value();
  float c = 0;
  float l = ar[0].value();
  for (uint8_t i = 0; i < len; i++)
  {
    a += ar[i].value();
    // find highest value
    c =  ar[i].value() + ar[i].error();
    if (c > h) h = c;
    // find lowest value
    c =  ar[i].value() - ar[i].error();
    if (c < l) l = c;
  }
  // average
  a /= len;

  // max error
  h = h - a;
  l = a - l;
  c = max(l, h);

  FLE x(a, c);
  x.setDecimals(dec);
  return x;
}


// -- END OF FILE --
