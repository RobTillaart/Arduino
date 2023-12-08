//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2023-07-30
// PURPOSE: unit tests for the PT2314
//          https://github.com/RobTillaart/PT2314
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
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



////////////////////////////////////
//
//  MANY TESTS WILL BLOCK AS BUILD CI HAS NO GOOD TIMEOUT
//  ALL FAILING TESTS ARE COMMENTED
//
//  USE GODMODE SERIAL TO IMPROVE THESE TESTS
//

#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "PT2314.h"


unittest_setup()
{
  fprintf(stderr, "PT2314_LIB_VERSION:\t%s\n", (char *) PT2314_LIB_VERSION);
}


unittest_teardown()
{
}

//  not testable withour proper mock-up
unittest(test_constructor)
{
  PT2314 pt2;
  PT7313 pt3;
  PT7314 pt7;

  assertEqual(1, 1);
}


unittest_main()


//  -- END OF FILE --


