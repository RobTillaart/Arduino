//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-07
// PURPOSE: unit tests for the SHEX Serial HEX library
//          https://github.com/RobTillaart/SHEX
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

#include "SHEX.h"


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_all)
{
  fprintf(stderr, "VERSION: %s\n", SHEX_LIB_VERSION);

  SHEX shex;
  
  assertFalse(shex.getHEX());
  shex.setHEX();
  assertTrue(shex.getHEX());
  shex.setHEX(false);
  assertFalse(shex.getHEX());

  assertEqual(16, shex.getBytesPerLine());
  shex.setBytesPerLine(60);
  assertEqual(32, shex.getBytesPerLine());
  shex.setBytesPerLine();
  assertEqual(16, shex.getBytesPerLine());

  assertEqual(' ', shex.getSeparator());
  shex.setSeparator('-');
  assertEqual('-', shex.getSeparator());
  shex.setSeparator();
  assertEqual(' ', shex.getSeparator());

  assertTrue(shex.getCountFlag());
  shex.setCountFlag(false);
  assertFalse(shex.getCountFlag());
  shex.setCountFlag();
  assertTrue(shex.getCountFlag());

}

unittest_main()

// --------
