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
  fprintf(stderr, "SHEX_LIB_VERSION: %s\n", (char *) SHEX_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(16, SHEX_DEFAULT_LENGTH);
  assertEqual(32, SHEX_MAX_LENGTH);
  assertEqual(4, SHEX_MIN_LENGTH);
  assertEqual(8, SHEX_DEFAULT_VTAB);
}


unittest(test_set_hex)
{
  SHEX shex;
  
  assertFalse(shex.getHEX());
  shex.setHEX();
  assertTrue(shex.getHEX());

  shex.setHEX(false);
  assertFalse(shex.getHEX());

  shex.setHEX();
  assertTrue(shex.getHEX());
}


unittest(test_bytes_per_line)
{
  SHEX shex(&Serial, 24);

  assertEqual(24, shex.getBytesPerLine());

  shex.setBytesPerLine(8);
  assertEqual(8, shex.getBytesPerLine());

  shex.setBytesPerLine(60);
  assertEqual(32, shex.getBytesPerLine());

  shex.setBytesPerLine();
  assertEqual(SHEX_DEFAULT_LENGTH, shex.getBytesPerLine());
}


unittest(test_separator)
{
  SHEX shex;

  assertEqual(' ', shex.getSeparator());

  shex.setSeparator('-');
  assertEqual('-', shex.getSeparator());

  shex.setSeparator();
  assertEqual(' ', shex.getSeparator());
}


unittest(test_countFlag)
{
  SHEX shex;

  assertTrue(shex.getCountFlag());
  shex.setCountFlag(false);
  assertFalse(shex.getCountFlag());
  shex.setCountFlag();
  assertTrue(shex.getCountFlag());
}


unittest(test_vtab)
{
  SHEX shex;

  assertEqual(8, shex.getVTAB());

  for (uint8_t vtab = 1; vtab < 9; vtab *= 2 )
  {
    shex.setVTAB(vtab);
    assertEqual(vtab, shex.getVTAB());
  }
}


unittest_main()

// --------
