//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-01-12
// PURPOSE: unit tests for the TCS3210 library
//          https://github.com/RobTillaart/TCS3210
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
#include "TCS3210.h"


unittest_setup()
{
  fprintf(stderr, "TCS3210_LIB_VERSION:\t%s\n", (char *) TCS3210_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor_TCS3210)
{
  TCS3210 TCS(4,5,6, 7,8,9);

  assertTrue(TCS.begin());
  assertEqual(10, TCS.getType());
}


unittest(test_constructor_TCS3200)
{
  TCS3200 TCS(4,5,6, 7,8,9);;

  assertTrue(TCS.begin());
  assertEqual(00, TCS.getType());
}


unittest_main()


//  -- END OF FILE --

