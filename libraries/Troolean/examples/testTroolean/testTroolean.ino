//
//    FILE: testTroolean.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test for troolean (tri state) math library for Arduino
//     URL: https://github.com/RobTillaart/Troolean


#include "Troolean.h"


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TROOLEAN_LIB_VERSION: ");
  Serial.println(TROOLEAN_LIB_VERSION);

  testConstructor();
  testEquality();
  testInEquality();
  testAssignment();
  testAND();
  testOR();
  testNOT();
  testIF();
  testIS();
}


void loop()
{
}


void testConstructor()
{
  Troolean f(false);
  Troolean t(true);
  Troolean u(-1);
  Troolean v(u);

  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.print(f);
  Serial.print('\t');
  Serial.print(t);
  Serial.print('\t');
  Serial.print(u);
  Serial.print('\t');
  Serial.println(v);
}


void testEquality()
{
  Troolean f(false);
  Troolean t(true);
  Troolean u(unknown);

  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.print(f == f);
  Serial.print('\t');
  Serial.print(f == t);
  Serial.print('\t');
  Serial.println(f == u);
  Serial.print(t == f);
  Serial.print('\t');
  Serial.print(t == t);
  Serial.print('\t');
  Serial.println(t == u);
  Serial.print(u == f);
  Serial.print('\t');
  Serial.print(u == t);
  Serial.print('\t');
  Serial.println(u == u);

  Serial.print(f == false);
  Serial.print('\t');
  Serial.print(t == true);
  Serial.print('\t');
  Serial.print(u == false);
  Serial.print('\t');
  Serial.println(u == true);
}


void testInEquality()
{
  Troolean f(false);
  Troolean t(true);
  Troolean u(-1);

  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.print(f != f);
  Serial.print('\t');
  Serial.print(f != t);
  Serial.print('\t');
  Serial.println(f != u);
  Serial.print(t != f);
  Serial.print('\t');
  Serial.print(t != t);
  Serial.print('\t');
  Serial.println(t != u);
  Serial.print(u != f);
  Serial.print('\t');
  Serial.print(u != t);
  Serial.print('\t');
  Serial.println(u != u);

  Serial.print(f != false);
  Serial.print('\t');
  Serial.print(t != true);
  Serial.print('\t');
  Serial.print(u != false);
  Serial.print('\t');
  Serial.println(u != true);
}


void testAssignment()
{
  Troolean f(false);
  Troolean t(true);
  Troolean u(-1);

  f = true;
  t = unknown;
  u = false;
  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.print(f);
  Serial.print('\t');
  Serial.print(t);
  Serial.print('\t');
  Serial.println(u);
}


void testAND()
{
  Troolean a, b, c;

  Serial.println();
  Serial.println(__FUNCTION__);
  a = true;
  b = false;
  c = a && b;
  Serial.print(c);
  Serial.print('\t');
  a = true;
  b = true;
  c = a && b;
  Serial.print(c);
  Serial.print('\t');
  a = true;
  b = unknown;
  c = a && b;
  Serial.println(c);

  a = false;
  b = false;
  c = a && b;
  Serial.print(c);
  Serial.print('\t');
  a = false;
  b = true;
  c = a && b;
  Serial.print(c);
  Serial.print('\t');
  a = false;
  b = unknown;
  c = a && b;
  Serial.println(c);

  a = unknown;
  b = false;
  c = a && b;
  Serial.print(c);
  Serial.print('\t');
  a = unknown;
  b = true;
  c = a && b;
  Serial.print(c);
  Serial.print('\t');
  a = unknown;
  b = unknown;
  c = a && b;
  Serial.println(c);
}


void testOR()
{
  Troolean a, b, c;

  Serial.println();
  Serial.println(__FUNCTION__);
  a = true;
  b = false;
  c = a || b;
  Serial.print(c);
  Serial.print('\t');
  a = true;
  b = true;
  c = a || b;
  Serial.print(c);
  Serial.print('\t');
  a = true;
  b = unknown;
  c = a || b;
  Serial.println(c);

  a = false;
  b = false;
  c = a || b;
  Serial.print(c);
  Serial.print('\t');
  a = false;
  b = true;
  c = a || b;
  Serial.print(c);
  Serial.print('\t');
  a = false;
  b = unknown;
  c = a || b;
  Serial.println(c);

  a = unknown;
  b = false;
  c = a || b;
  Serial.print(c);
  Serial.print('\t');
  a = unknown;
  b = true;
  c = a || b;
  Serial.print(c);
  Serial.print('\t');
  a = unknown;
  b = unknown;
  c = a || b;
  Serial.println(c);
}


void testNOT()
{
  Troolean a(false), b(true), c(unknown);

  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.print(!a);
  Serial.print('\t');
  Serial.print(!b);
  Serial.print('\t');
  Serial.println(!c);

  Serial.print(!!a);
  Serial.print('\t');
  Serial.print(!!b);
  Serial.print('\t');
  Serial.println(!!c);
}


void testIF()
{
  // a troolean cannot be used directly in a if or while statement
  // it must be compared to either boolean ot troolean.
  Troolean a(false), b(true), c(unknown);

  Serial.println();
  Serial.println(__FUNCTION__);

  Serial.print("TRUE");
  Serial.print('\t');
  if (a == true)
  {
    Serial.print('a');
    Serial.print('\t');
  }
  if (b == true)
  {
    Serial.print('b');
    Serial.print('\t');
  }
  if (c == true)
  {
    Serial.print('c');
    Serial.print('\t');
  }
  Serial.println();

  Serial.print("FALSE");
  Serial.print('\t');
  if (a == false)
  {
    Serial.print('a');
    Serial.print('\t');
  }
  if (b == false)
  {
    Serial.print('b');
    Serial.print('\t');
  }
  if (c == false)
  {
    Serial.print('c');
    Serial.print('\t');
  }
  Serial.println();

  Serial.print("UNKNOWN");
  Serial.print('\t');
  if (a == unknown)
  {
    Serial.print('a');
    Serial.print('\t');
  }
  if (b == unknown)
  {
    Serial.print(b);
    Serial.print('b');
    Serial.print('\t');
  }
  if (c == unknown)
  {
    Serial.print('c');
    Serial.print('\t');
  }
  Serial.println();

  Serial.print("BOOL()");
  Serial.print('\t');
  if (a)
  {
    Serial.print('a');
    Serial.print('\t');
  }
  if (b)
  {
    Serial.print('b');
    Serial.print('\t');
  }
  if (c)
  {
    Serial.print('c');
    Serial.print('\t');
  }
  Serial.println();
}


void testIS()
{
  Troolean f(false), t(true), u(unknown);

  Serial.println();
  Serial.println(__FUNCTION__);

  Serial.print(f.isFalse());
  Serial.print('\t');
  Serial.print(f.isTrue());
  Serial.print('\t');
  Serial.println(f.isUnknown());

  Serial.print(t.isFalse());
  Serial.print('\t');
  Serial.print(t.isTrue());
  Serial.print('\t');
  Serial.println(t.isUnknown());

  Serial.print(u.isFalse());
  Serial.print('\t');
  Serial.print(u.isTrue());
  Serial.print('\t');
  Serial.println(u.isUnknown());

  Serial.println();
}


////////////////////////////////////////////////////////////
//
// EXPECTED OUTPUT
//
/*
  .....\test1.ino
TROOLEAN_LIB_VERSION: 0.1.1

testConstructor
false	true	unknown	unknown

testEquality
1	0	0
0	1	0
0	0	1
1	1	0	0

testInEquality
0	1	1
1	0	1
1	1	0
0	0	1	1

testAssignment
true	unknown	false

testAND
false	true	unknown
false	false	false
false	unknown	unknown

testOR
true	true	true
false	true	unknown
unknown	true	unknown

testNOT
true	false	unknown
false	true	unknown

testIF
TRUE	b	
FALSE	a	
UNKNOWN	c	
BOOL()	trueb	

testIS
1	0	0
0	1	0
0	0	1

*/


// -- END OF FILE --

