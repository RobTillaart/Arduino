//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-09
// PURPOSE: unit tests for the timing libraty
//          https://github.com/RobTillaart/timing
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
#include "timing.h"


unittest_setup()
{
  fprintf(stderr, "TIMING_LIB_VERSION: %s\n", (char *) TIMING_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  microSeconds mic;
  assertEqual(0, mic.getOffset());
  mic.set(100);
  assertEqual(4294967196, mic.getOffset());  // max uint32_t - 100

  milliSeconds mil;
  assertEqual(0, mil.getOffset());
  mil.set(100);
  assertEqual(4294967196, mil.getOffset());

  seconds sec;
  assertEqual(0, sec.getOffset());
  sec.set(100);
  assertEqual(4294967196, sec.getOffset());

  fprintf(stderr, "%d\n", mic.now());
  fprintf(stderr, "%d\n", mil.now());
  fprintf(stderr, "%d\n", sec.now());
}


unittest_main()


//  --END OF FILE --

