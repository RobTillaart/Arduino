//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-02
// PURPOSE: unit tests for the multiMap
//          https://github.com/RobTillaart/MultiMap
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


#include "MultiMap.h"


unittest_setup()
{
}

unittest_teardown()
{
}

/*
unittest(test_new_operator)
{
  assertEqualINF(exp(800));
  assertEqualINF(0.0/0.0);
  assertEqualINF(42);
  
  assertEqualNAN(INFINITY - INFINITY);
  assertEqualNAN(0.0/0.0);
  assertEqualNAN(42);
}
*/

unittest(test_all)
{
  fprintf(stderr, "VERSION: %s\n", MULTIMAP_LIB_VERSION);
  
  // based on the distance example
  // out[] holds the distances in cm
  float out[] = {150, 140, 130, 120, 110, 100, 90, 80, 70, 60, 50, 40, 30, 20};
  // in[] holds the measured analogRead() values for that distance
  float in[]  = { 90, 97, 105, 113, 124, 134, 147, 164, 185, 218, 255, 317, 408, 506};

  assertEqualFloat(150.000, multiMap<float>(80, in, out, 14), 0.001);
  assertEqualFloat(136.250, multiMap<float>(100, in, out, 14), 0.001);
  assertEqualFloat(65.4545, multiMap<float>(200, in, out, 14), 0.001);
  assertEqualFloat(42.7419, multiMap<float>(300, in, out, 14), 0.001);
  assertEqualFloat(30.8791, multiMap<float>(400, in, out, 14), 0.001);
  assertEqualFloat(20.6122, multiMap<float>(500, in, out, 14), 0.001);
  assertEqualFloat(20.0000, multiMap<float>(600, in, out, 14), 0.001);
}

unittest_main()

// --------
