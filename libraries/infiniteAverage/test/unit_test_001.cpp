//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-28
// PURPOSE: unit tests for the infiniteAverage
//          https://github.com/RobTillaart/infiniteAverage
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


#include "infiniteAverage.h"


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  fprintf(stderr, "VERSION: %s\n", IAVG_LIB_VERSION);

  IAVG iavg;
  
  assertEqual(0, iavg.count());
  assertEqual(0, iavg.whole());
  assertEqualFloat(0, iavg.decimals(), 0.0001);
}


unittest(test_add)
{
  fprintf(stderr, "VERSION: %s\n", IAVG_LIB_VERSION);

  IAVG iavg;

  iavg.add(10000000);
  assertEqual(1, iavg.count());
  assertEqual(10000000, iavg.whole());
  assertEqualFloat(0, iavg.decimals(), 0.0001);
  assertEqualFloat(10000000, iavg.average(), 0.0001);

  iavg.add(1);
  assertEqual(2, iavg.count());
  assertEqual(10000001, iavg.whole());
  assertEqualFloat(0, iavg.decimals(), 0.0001);
  assertEqualFloat(5000000.5, iavg.average(), 0.5);  // as output is just a float ...
}


unittest_main()

// --------
