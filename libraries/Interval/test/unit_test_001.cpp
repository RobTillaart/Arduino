//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-30
// PURPOSE: unit tests for the Interval library
//          https://github.com/RobTillaart/Interval
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
#include "Interval.h"



unittest_setup()
{
  fprintf(stderr, "INTERVAL_LIB_VERSION: %s\n", INTERVAL_LIB_VERSION );
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  Interval x(1, 5);
  assertEqual(1, x.low());
  assertEqual(5, x.high());
  assertEqual(4, x.range());
  assertEqual(3, x.value());
  assertEqualFloat(1.333333, x.relAccuracy(), 0.0001);
}


unittest(test_math_basic_1)
{
  Interval x(1, 5);
  Interval y(2, 3);
  Interval z;

  fprintf(stderr, "x + y\n");
  z = x + y;
  assertEqual(3, z.low());
  assertEqual(8, z.high());
  assertEqual(5, z.range());
  assertEqual(5.5, z.value());
  assertEqualFloat(0.909091, z.relAccuracy(), 0.0001);

  fprintf(stderr, "x - y\n");
  z = x - y;
  assertEqual(-2, z.low());
  assertEqual(3, z.high());
  assertEqual(5, z.range());
  assertEqual(0.5, z.value());
  assertEqualFloat(10, z.relAccuracy(), 0.0001);

  fprintf(stderr, "x * y\n");
  z = x * y;
  assertEqual(2, z.low());
  assertEqual(15, z.high());
  assertEqual(13, z.range());
  assertEqual(8.5, z.value());
  assertEqualFloat(1.52941, z.relAccuracy(),0.0001);

  fprintf(stderr, "x / y\n");
  z = x / y;
  assertEqualFloat(0.333333, z.low(), 0.0001);
  assertEqualFloat(2.5, z.high(), 0.0001);
  assertEqualFloat(2.16667, z.range(), 0.0001);
  assertEqualFloat(1.41667, z.value(), 0.0001);
  assertEqualFloat(1.52941, z.relAccuracy(), 0.0001);

  fprintf(stderr, "x - x\n");
  z = x - x;  // 0;
  assertEqual(-4, z.low());
  assertEqual(4, z.high());
  assertEqual(8, z.range());
  assertEqual(0, z.value());
  assertEqual(-1, z.relAccuracy());  // NAN equivalent
}


unittest(test_math_basic_2)
{
  Interval x(1, 5);
  Interval y(2, 3);

  fprintf(stderr, "x += y\n");
  x += y;
  assertEqual(3, x.low());
  assertEqual(8, x.high());
  assertEqual(5, x.range());
  assertEqual(5.5, x.value());
  assertEqualFloat(0.909091, x.relAccuracy(), 0.0001);

  fprintf(stderr, "x -= y\n");
  x -= y;
  assertEqual(0, x.low());
  assertEqual(6, x.high());
  assertEqual(6, x.range());
  assertEqual(3, x.value());
  assertEqualFloat(2, x.relAccuracy(), 0.0001);

  fprintf(stderr, "x *= y\n");
  x *= y;
  assertEqual(0, x.low());
  assertEqual(18, x.high());
  assertEqual(18, x.range());
  assertEqual(9, x.value());
  assertEqualFloat(2, x.relAccuracy(),0.0001);

  fprintf(stderr, "x /= y\n");
  x /= y;
  assertEqualFloat(0, x.low(), 0.0001);
  assertEqualFloat(9, x.high(), 0.0001);
  assertEqualFloat(9, x.range(), 0.0001);
  assertEqualFloat(4.5, x.value(), 0.0001);
  assertEqualFloat(2, x.relAccuracy(), 0.0001);
}


unittest(test_comparisons)
{
  Interval x(1, 5);
  Interval y(2, 3);
  Interval a(1, 5);
  Interval b(2, 3);

  assertTrue(x == x);
  assertTrue(x == a);
  assertFalse(x == y);

  assertFalse(x != x);
  assertFalse(x != a);
  assertTrue(x != y);

  // assertFalse(x < x);
  // assertFalse(x < a);
  // assertFalse(x < y);
  // 
  // assertTrue(x <= x);
  // assertTrue(x <= a);
  // assertFalse(x <= y);
  // 
  // assertFalse(x > x);
  // assertFalse(x > a);
  // assertFalse(x > y);
  // 
  // assertTrue(x >= x);
  // assertTrue(x >= a);
  // assertFalse(x >= y);
}


unittest_main()


// --------
