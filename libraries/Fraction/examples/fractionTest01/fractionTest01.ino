//
//    FILE: fractionTest01.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test sketch for fraction math
//     URL: https://github.com/RobTillaart/Fraction


#include "fraction.h"


Fraction q(0.42);
Fraction a(1, 3);
Fraction aa(3, 9);
Fraction b(1, 4);
Fraction n(0, 5);
Fraction p(5, 1);
Fraction pi(PI);
Fraction e(EULER);
Fraction gr(1.6180339887498948482);  //  golden ratio


void setup()
{
  Serial.begin(115200);
  Serial.print("Start fractionTest: ");
  Serial.println(FRACTION_LIB_VERSION);
  Serial.println();

  Serial.println(a.toString());
  Serial.println(aa.toString());
  Serial.println(b.toString());
  Serial.println(n.toString());
  Serial.println(p.toString());
  Serial.println(q.toString());
  Serial.println(pi.toString());
  Serial.println(e.toString());
  Serial.println(Fraction::middle(pi, e).toString());
  Serial.println(Fraction::mediant(pi, e).toString());
  Serial.println(gr.toString());
  Serial.println();

  testPlus();
  testMin();
  testMul();
  testDiv();

  testEQ();
  testNEQ();
  testLS();
  testLE();
  testGR();
  testGE();
}


void loop()
{
}


void testPlus()
{
  Serial.println("testPlus");
  Serial.println((a + b).toString());
  Fraction c = a + b;
  Serial.println(c.toString());
  c = a;
  c += b;
  Serial.println(c.toString());
  Serial.println();
  Serial.println();
}


void testMin()
{
  Serial.println("testMin");
  Serial.println((a - b).toString());
  Fraction c = a - b;
  Serial.println(c.toString());
  c = a;
  c -= b;
  Serial.println(c.toString());
  Serial.println();
  Serial.println();
}


void testMul()
{
  Serial.println("testMul");
  Serial.println((a * b).toString());
  Fraction c = a * b;
  Serial.println(c.toString());
  c = a;
  c *= b;
  Serial.println(c.toString());
  Serial.println();
  Serial.println();
}


void testDiv()
{
  Serial.println("testDiv");
  Serial.println((a / b).toString());
  Fraction c = a / b;
  Serial.println(c.toString());
  c = a;
  c /= b;
  Serial.println(c.toString());
  Serial.println();
  Serial.println();
}


void testEQ()
{
  Serial.println("testEQ 0 1 1");
  Serial.println(a == b);
  Serial.println(a == a);
  Serial.println(a == aa);
  Serial.println();
  Serial.println();
}


void testNEQ()
{
  Serial.println("testNEQ 1 0 0");
  Serial.println(a != b);
  Serial.println(a != a);
  Serial.println(a != aa);
  Serial.println();
  Serial.println();
}


void testLS()
{
  Serial.println("testLS 0 0");
  Serial.println(a < b);
  Serial.println(a < a);
  Serial.println();
  Serial.println();
}


void testLE()
{
  Serial.println("testLE 0 1");
  Serial.println(a <= b);
  Serial.println(a <= a);
  Serial.println();
  Serial.println();
}


void testGR()
{
  Serial.println("testGR 1 0");
  Serial.println(a > b);
  Serial.println(a > a);
  Serial.println();
  Serial.println();
}


void testGE()
{
  Serial.println("testGE 1 1");
  Serial.println(a >= b);
  Serial.println(a >= a);
  Serial.println();
  Serial.println();
}


//  -- END OF FILE --
