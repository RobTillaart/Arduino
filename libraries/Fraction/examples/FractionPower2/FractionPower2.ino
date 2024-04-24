//
//    FILE: FractionPower2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Find fraction with powers of 2.
//     URL: https://github.com/RobTillaart/Fraction
//
//  this method is very fast as it calculates a fraction in one step with an accuracy
//  of 1/8192. Quality is limited due the limited range of denominators.
//
//  a slow variant that adds powers of two is added to show some math.


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
  Fraction sum(round(f*8192), 8192);
  return sum;
}


//  Slow_fractionize works only for range 0..1
Fraction slow_fractionize(float f)
{
  Fraction sum(0, 1);
  Fraction b(1, 2);

  for (int i = 0; i < 25; i++)  //  might need less 
  {
    Fraction tmp = sum + b;
    if (tmp.toFloat() < f) sum = tmp;
    b /= 2;
  }
  return sum;
}


//  -- END OF FILE --
