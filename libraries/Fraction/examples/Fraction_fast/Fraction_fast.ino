//
//    FILE: Fraction_fast.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Calculate fraction with well chosen number.
//     URL: https://github.com/RobTillaart/Fraction
//
//  This method is very fast as it calculates a fraction in one step.
//  It uses a default denominator of 9900 which is consists of several 
//  small prime factors, to improve the chance of simplifying.
//  - very fast
//  - constant accuracy in the order of 1e-4.
//  - limited set of denominators after simplifying.
//  P(9900) = {2, 2, 3, 3, 5, 5, 11}
//
//  other explored options:
//  P(19800) = {2, 2, 2, 3, 3, 5, 5, 11} (add factor 2 factor)
//  P(10800) = {2, 2, 2, 2, 3, 3, 3, 5, 5}
//  P(9240)  = {2, 2, 2, 3, 5, 7, 11}
//  P(13860) = {2, 2, 3, 3, 5, 7, 11}
//  P(30030) = {2, 3, 5, 7, 11, 13}


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


Fraction fractionize(float f)
{
  Fraction value(round(f * 9900), 9900);
  return value;
}


//  -- END OF FILE --
