//
//    FILE: FractionMediant.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Find fraction by binary search with mediant.
//     URL: https://github.com/RobTillaart/Fraction
//
//  This method is not fast but it shows an application for the mediant().
//  Works for positive values only (for now).


#include "fraction.h"


uint32_t start, stop;


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

  float f = PI;
  start = micros();
  Fraction x = fractionize(f);
  stop = micros();
  Serial.println(stop - start);
  Serial.println(x.toString());
  Serial.println(x.toDouble(), 10);
  Serial.println();
  delay(100);

  f = EULER;
  start = micros();
  Fraction y = fractionize(f);
  stop = micros();
  Serial.println(stop - start);
  Serial.println(y.toString());
  Serial.println(y.toDouble(), 10);
  Serial.println();
  delay(100);

  Serial.println("done...\n");
  delay(100);
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
  delay(100);

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
  delay(100);
}


Fraction fractionize(float f)
{
  float accuracy = 1e-6;
  int i;
  Fraction a(0, 1);
  Fraction b(uint16_t(f) + 1, 1);
  Fraction c;

  for (i = 0; i < 500; i++)
  {
    c = Fraction::mediant(a, b);   //  NOTE middle(a, b) is slower and worse!
    float t = c.toDouble();
    if ( t < f) a = c;
    else b = c;
    //  check the last found value.
    if (abs(f - t) < accuracy) break;
  }
  Serial.println(i);
  return c;
}


//  -- END OF FILE --
