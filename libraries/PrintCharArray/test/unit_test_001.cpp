//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-01
// PURPOSE: unit tests for the PrintCharArray library
//          https://github.com/RobTillaart/PrintCharArray
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
#include "PrintCharArray.h"


unittest_setup()
{
  fprintf(stderr, "PRINTCHARARRAY_VERSION: %s\n", (char *) PRINTCHARARRAY_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(PRINTCHARARRAY_MAX_BUFFER_SIZE, 250);
}


unittest(test_constructor)
{
  PrintCharArray ps(100);

  assertEqual(100, ps.bufSize());
  assertEqual(100, ps.available());
  assertEqual(0,   ps.size());

  ps.print("Hello World");
  fprintf(stderr, "%s\n", ps.getBuffer());
  assertEqual(89, ps.available());
  assertEqual(11, ps.size());

  ps.print(" and moon");
  fprintf(stderr, "%s\n", ps.getBuffer());
  assertEqual(80, ps.available());
  assertEqual(20, ps.size());

  ps.clear();
  assertEqual(100, ps.available());
  assertEqual(0,   ps.size());
}


unittest_main()

// --------
