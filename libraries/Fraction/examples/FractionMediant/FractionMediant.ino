//
//    FILE: FractionMediant.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Find fraction by binary search with mediant.
//    DATE: 2020-04-21
//
// this method is not that fast but it shows a nice application for 
// the mediant.


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
  Serial.println(x);
  Serial.println(x.toDouble(), 10);
  Serial.println();

  f = EULER;
  start = micros();
  Fraction y = fractionize(f);
  stop = micros();
  Serial.println(stop - start);
  Serial.println(y);
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
  Serial.print(y);
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
  Serial.print(y);
  Serial.print("\t");
  Serial.print(f, 10);
  Serial.print("\t");
  Serial.print(y.toDouble(), 10);
  Serial.print("\t");
  Serial.println(f - y.toDouble(), 10);
}


Fraction fractionize(float f)
{
  float acc = 1e-6;
  float d1 = 0;
  float d2 = 0;
  Fraction a(0, 1);
  Fraction b(9999, 1);
  Fraction q(f);

  for (int i = 0; i < 500; i++)
  {
    Fraction c = Fraction::mediant(a, b);   // NOTE middle(a,b) is slower and worse!
    if ( c.toDouble() < f) a = c;
    else b = c;

    d1 = abs(f - a.toDouble());
    d2 = abs(f - b.toDouble());
    if (d1 < acc && d2 < acc) break;
  }
  if (d1 < d2) return a;
  return b;
}


// -- END OF FILE --

