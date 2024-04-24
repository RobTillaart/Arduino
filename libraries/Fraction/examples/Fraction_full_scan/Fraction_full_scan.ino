//
//    FILE: Fraction_full_scan.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Find fraction by full scan possible values.
//     URL: https://github.com/RobTillaart/Fraction
//
//  This method is very slow but it scans the whole range (in fact only half)
//  for all possible fractions, resulting in very good approximations.
//  Works for positive values only (for now).
//
//  Takes up to 3 seconds per search on a 16 MHz UNO.
//  Takes up to 12 milliseconds per search on a 240 MHz ESP32.

#include "fraction.h"


uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.print(__FILE__);
  Serial.println();
  Serial.println();

  float f = PI;
  start = micros();
  Fraction x = fractionize(f);
  stop = micros();
  Serial.println(stop - start);
  Serial.println(x.toString());
  Serial.println(x.toDouble(), 10);
  Serial.println();

  f = EULER;
  start = micros();
  Fraction y = fractionize(f);
  stop = micros();
  Serial.println(stop - start);
  Serial.println(y.toString());
  Serial.println(y.toDouble(), 10);
  Serial.println();

  Serial.println("done...\n");
}


void loop()
{
  float f = random(1000000) * 0.000001;

  // reference
  start = micros();
  Fraction y(f);
  stop = micros();

  Serial.println();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(y.toString());
  Serial.print("\t");
  Serial.print(f, 10);
  Serial.print("\t");
  Serial.print(y.toDouble(), 10);
  Serial.print("\t");
  Serial.println(f - y.toDouble(), 10);

  // mediant method.
  start = micros();
  y = fractionize(f);
  stop = micros();

  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(y.toString());
  Serial.print("\t");
  Serial.print(f, 10);
  Serial.print("\t");
  Serial.print(y.toDouble(), 10);
  Serial.print("\t");
  Serial.println(f - y.toDouble(), 10);
}

// very very slow but very good.
Fraction fractionize(float f)
{
  int best = 1;
  float smallest = 1.0;
  //  smaller denominators will all be detected as 5000..10000 are multiples.
  for (int d = 5000; d < 10000; d++)
  {
    Fraction frac(f * d + 0.5, d);
    float tmp = abs(f - frac.toFloat());
    if ( tmp < smallest)
    {
      smallest = tmp;
      best = d;
    }
  }
  Fraction frac(round(f * best), best);
  return frac;
}


//  -- END OF FILE --
