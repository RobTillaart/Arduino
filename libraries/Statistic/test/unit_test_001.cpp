//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-08
// PURPOSE: unit tests for the Statistic library
//          https://github.com/RobTillaart/Statistic
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
#include "Statistic.h"


unittest_setup()
{
  fprintf(stderr, "\nSTATISTIC_LIB_VERSION: %s\n", (char *) STATISTIC_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  Statistic myStats;
  assertEqual(0, myStats.count());
}


unittest(test_basic)
{
  Statistic myStats;

  for (int i = 1; i < 100; i++) myStats.add(i);
  assertEqual(99, myStats.count());
  assertEqualFloat(4950,    myStats.sum(),       0.0001);
  assertEqualFloat(1,       myStats.minimum(),   0.0001);
  assertEqualFloat(50,      myStats.average(),   0.0001);
  assertEqualFloat(99,      myStats.maximum(),   0.0001);
  assertEqualFloat(816.667, myStats.variance(),  0.001);     // note 1 digit less
  assertEqualFloat(28.5774, myStats.pop_stdev(), 0.0001);
  assertEqualFloat(28.7228, myStats.unbiased_stdev(), 0.0001);

  myStats.clear();
  assertEqualFloat(0,   myStats.sum(),       0.0001);
  assertEqualFloat(0,   myStats.minimum(),   0.0001);
  assertEqualFloat(0,   myStats.average(),   0.0001);
  assertEqualFloat(0,   myStats.maximum(),   0.0001);
  assertEqualFloat(0,   myStats.variance(),  0.0001);
  assertEqualFloat(0,   myStats.pop_stdev(), 0.0001);
  assertEqualFloat(0,   myStats.unbiased_stdev(), 0.0001);

  assertEqual(0, myStats.count());
}


unittest_main()


//  -- END OF FILE --

