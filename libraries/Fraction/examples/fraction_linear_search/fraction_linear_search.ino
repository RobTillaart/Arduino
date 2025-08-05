//    FILE: fraction_linear_search.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2024-11-21
// PURPOSE: test
//     URL: https://github.com/RobTillaart/Fraction

#include "fraction.h"

uint32_t start, stop;

float value = 0.1258;

void setup()
{
  //  while(!Serial);  //  Leonardo
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println("FRACTION_LIB_VERSION: ");
  Serial.println(FRACTION_LIB_VERSION);
  Serial.println();
  delay(100);

  start = micros();
  uint32_t a = 0;
  uint32_t b = 1;
  uint32_t p = a;
  uint32_t q = b;
  float s = abs(value * q - p);

  while ( b <= 100)
  {
    float t = value * b - a;
    //  found
    if (abs(t) < 0.00001)
    {
      p = a;
      q = b;
      break;
    }
    //  best so far
    if (abs(t) < s)
    {
      s = abs(t);
      p = a;
      q = b;
    }
    //  try next tuple
    if (t > 0) a++;
    b++;
  }
  stop = micros();

  Serial.print(value, 6);
  Serial.print(" = ");
  Serial.print(p);
  Serial.print(" / ");
  Serial.print(q);
  Serial.println();

  Serial.print("TIME: ");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

  start = micros();
  Fraction xx(value);
  stop = micros();
  Serial.println(xx.toDouble(), 4);
  Serial.println(xx.toString());
  Serial.print("TIME: ");
  Serial.print(stop - start);
  Serial.println();
  delay(100);

}

void loop()
{
}


/*
     while ( b <= 1000)
  {
    float t = value * b - a;
    //  found
    if (abs(t) < 0.00001)
    {
      p = a;
      q = b;
      break;
    }
    //  best so far
    if (abs(t) < s)
    {
      s = abs(t);
      p = a;
      q = b;
    }
    //  try next tuple
    if (t > 0) a++;
    else b *= 2;  <<<<<<<<<<<  binary search
  }
  stop = micros();
*/


//  -- END OF FILE --
