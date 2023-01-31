//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2020-12-03
// PURPOSE: unit tests for the Angle library
//          https://github.com/RobTillaart/Angle
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual);               // a == b
// assertNotEqual(unwanted, actual);            // a != b
// assertComparativeEquivalent(expected, actual);    // abs(a - b) == 0 or (!(a > b) && !(a < b))
// assertComparativeNotEquivalent(unwanted, actual); // abs(a - b) > 0  or ((a > b) || (a < b))
// assertLess(upperBound, actual);              // a < b
// assertMore(lowerBound, actual);              // a > b
// assertLessOrEqual(upperBound, actual);       // a <= b
// assertMoreOrEqual(lowerBound, actual);       // a >= b
// assertTrue(actual);
// assertFalse(actual);
// assertNull(actual);

// // special cases for floats
// assertEqualFloat(expected, actual, epsilon);    // fabs(a - b) <= epsilon
// assertNotEqualFloat(unwanted, actual, epsilon); // fabs(a - b) >= epsilon
// assertInfinity(actual);                         // isinf(a)
// assertNotInfinity(actual);                      // !isinf(a)
// assertNAN(arg);                                 // isnan(a)
// assertNotNAN(arg);                              // !isnan(a)


#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "Angle.h"


unittest_setup()
{
  fprintf(stderr, "ANGLE_LIB_VERSION: %s\n", (char *) ANGLE_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructors)
{
  Angle a(1, 2, 3, 4);
  Angle b(-45, 30);
  Angle n(0);
  Angle d(5.25);
  Angle s("37.25");

  assertEqual(1, a.sign());
  assertEqual(1, a.degree());
  assertEqual(2, a.minute());
  assertEqual(3, a.second());
  assertEqual(4, a.tenthousand());

  assertEqual(-1, b.sign());
  assertEqual(45, b.degree());
  assertEqual(30, b.minute());
  assertEqual(0, b.second());
  assertEqual(0, b.tenthousand());

  assertEqual(1, n.sign());
  assertEqual(0, n.degree());
  assertEqual(0, n.minute());
  assertEqual(0, n.second());
  assertEqual(0, n.tenthousand());

  assertEqual(1, d.sign());
  assertEqual(5, d.degree());
  assertEqual(15, d.minute());
  assertEqual(0, d.second());
  assertEqual(0, d.tenthousand());

  assertEqual(1, s.sign());
  assertEqual(37, s.degree());
  assertEqual(15, s.minute());
  assertEqual(0, s.second());
  assertEqual(0, s.tenthousand());
}


unittest(test_toDouble)
{
  Angle a(1, 2, 3, 4);
  Angle b(-45, 30);
  Angle n(0);
  Angle d(5.25);
  Angle s("37.25");

  float fa = a.toDouble();
  float fb = b.toDouble();
  float fn = n.toDouble();
  float fd = d.toDouble();
  float fs = s.toDouble();

  assertMoreOrEqual(2, fa);
  assertMoreOrEqual(-45, fb);
  assertEqual(0, fn);
  assertMoreOrEqual(6, fd);
  assertMoreOrEqual(38, fs);
}


unittest(test_Radians)
{
  Angle a(1, 2, 3, 4);
  Angle b(-75, 30);
  Angle n(0);
  Angle d(5.25);
  Angle s("91.25");

  float ra = a.toRadians();
  float rb = b.toRadians();
  float rn = n.toRadians();
  float rd = d.toRadians();
  float rs = s.toRadians();

  assertMoreOrEqual(1, ra);
  assertMoreOrEqual(-1, rb);
  assertEqual(0, rn);
  assertMoreOrEqual(0.1, rd);
  assertMoreOrEqual(PI, rs);  
}


//  mainly tests if operators still work, not a quality test (yet)
unittest(test_math)
{
  Angle a(1, 2, 3, 4);
  Angle b(-45, 30);
  Angle n(0);
  Angle d(5.25);
  Angle s("91.25");

  Angle x = a + b - n + d + s;
  assertNotEqual(0, x.toDouble());

  x *= 2;
  assertNotEqual(0, x.toDouble());
  x /= 2;
  assertNotEqual(0, x.toDouble());
  x += 2;
  assertNotEqual(0, x.toDouble());
  x -= 2;
  assertNotEqual(0, x.toDouble());

  x = a * 2;
  assertNotEqual(0, x.toDouble());
  x = a / 2;
  assertNotEqual(0, x.toDouble());
  x = a + 2;
  assertNotEqual(0, x.toDouble());
  x = a - 2;
  assertNotEqual(0, x.toDouble());
  
  x = -x;
  assertNotEqual(0, x.toDouble());
}


unittest(test_compare)
{
  Angle a(1, 2, 3, 4);
  Angle b(-45, 30);

  assertTrue(a == a);
  assertTrue(a != b);
  assertTrue(b <= a);
  assertTrue(b <  a);
  assertTrue(a >  b);
  assertTrue(a >= b);
}


unittest_main()


//  -- END OF FILE --

