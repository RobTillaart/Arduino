//
//    FILE: fractionTest01.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: test sketch for fraction math
//    DATE:
//     URL:
//
// Released to the public domain
//

#include "fraction.h"

Fraction q(0.42);
Fraction a(1, 3);
Fraction aa(3, 9);
Fraction b(1, 4);
Fraction n(0, 5);
Fraction p(5);
Fraction pi(PI);

void setup()
{
  Serial.begin(115200);
  Serial.print("Start fractionTest: ");
  Serial.println(FRACTIONLIBVERSION);
  Serial.println();

  Serial.println(a);
  Serial.println(aa);
  Serial.println(b);
  Serial.println(n);
  Serial.println(p);
  Serial.println(q);
  Serial.println(pi);
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
  Serial.println(a + b);
  Fraction c = a + b;
  Serial.println(c);
  c = a;
  c += b;
  Serial.println(c);
  Serial.println();
  Serial.println();
}

void testMin()
{
  Serial.println("testMin");
  Serial.println(a - b);
  Fraction c = a - b;
  Serial.println(c);
  c = a;
  c -= b;
  Serial.println(c);
  Serial.println();
  Serial.println();
}

void testMul()
{
  Serial.println("testMul");
  Serial.println(a * b);
  Fraction c = a * b;
  Serial.println(c);
  c = a;
  c *= b;
  Serial.println(c);
  Serial.println();
  Serial.println();
}

void testDiv()
{
  Serial.println("testDiv");
  Serial.println(a / b);
  Fraction c = a / b;
  Serial.println(c);
  c = a;
  c /= b;
  Serial.println(c);
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

