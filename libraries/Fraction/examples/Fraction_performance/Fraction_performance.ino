//
//    FILE: fractionTest01.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test sketch for fraction math
//     URL: https://github.com/RobTillaart/Fraction


#include "fraction.h"

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FRACTION_LIB_VERSION: ");
  Serial.println(FRACTION_LIB_VERSION);
  Serial.println();

  test_constructor();
  test_math();
  test_conversion();
  test_misc();

  Serial.println("\ndone...");
}


void loop()
{
}

void test_constructor()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(10);

  start = micros();
  Fraction q(0.42);
  Fraction a(1, 3);
  Fraction aa(3, 9);
  Fraction b(1, 4);
  Fraction n(0, 5);
  Fraction p(5, 1);
  Fraction pi(PI);
  Fraction e(EULER);
  stop = micros();
  Serial.print("TIME: \t");
  Serial.println(stop - start);

  Serial.println(q.toString());
  Serial.println(a.toString());
  Serial.println(aa.toString());
  Serial.println(b.toString());
  Serial.println(n.toString());
  Serial.println(p.toString());
  Serial.println(pi.toString());
  Serial.println(e.toString());
}


void test_math()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  delay(10);
  Fraction a(0, 1);
  Fraction pi(PI);
  Fraction e(EULER);
  start = micros();
  a = pi + e;
  stop = micros();
  Serial.print("TIME +: \t");
  Serial.println(stop - start);
  Serial.println(a.toString());

  delay(10);
  start = micros();
  a = pi - e;
  stop = micros();
  Serial.print("TIME -: \t");
  Serial.println(stop - start);
  Serial.println(a.toString());

  delay(10);
  start = micros();
  a = pi * e;
  stop = micros();
  Serial.print("TIME *: \t");
  Serial.println(stop - start);
  Serial.println(a.toString());

  delay(10);
  start = micros();
  a = pi / e;
  stop = micros();
  Serial.print("TIME /: \t");
  Serial.println(stop - start);
  Serial.println(a.toString());
}


void  test_conversion()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  delay(10);
  Fraction e(EULER);
  double d;
  start = micros();
  d = e.toDouble();
  stop = micros();
  Serial.print("TIME toDouble(): \t");
  Serial.println(stop - start);
  Serial.println(d, 7);

  delay(10);
  start = micros();
  d = e.toFloat();
  stop = micros();
  Serial.print("TIME toFloat(): \t");
  Serial.println(stop - start);
  Serial.println(d, 7);

  delay(10);
  start = micros();
  d = e.toAngle();
  stop = micros();
  Serial.print("TIME toAngle(): \t");
  Serial.println(stop - start);
  Serial.println(d, 7);
}


void  test_misc()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  delay(10);
  Fraction a(0, 1);
  Fraction pi(PI);
  Fraction e(EULER);
  start = micros();
  a = Fraction::mediant(pi, e);
  stop = micros();
  Serial.print("TIME mediant(): \t");
  Serial.println(stop - start);
  Serial.println(a.toString());

  delay(10);
  start = micros();
  a = Fraction::middle(pi, e);
  stop = micros();
  Serial.print("TIME middle(): \t");
  Serial.println(stop - start);
  Serial.println(a.toString());
}


//  -- END OF FILE --
