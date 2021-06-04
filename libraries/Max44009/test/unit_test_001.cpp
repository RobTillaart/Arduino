//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-30
// PURPOSE: unit tests for the Max44009
//          https://github.com/RobTillaart/Max44009
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
#include "Max44009.h"


unittest_setup()
{
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  fprintf(stderr, "VERSION: %s\n", MAX44009_LIB_VERSION);

  Max44009 LuxA(0x4A);
  Wire.begin();

  assertEqual(MAX44009_OK, LuxA.getError());
  assertTrue(LuxA.isConnected());   // TODO should be false...

  // TODO more tests if WIRE works...
}


unittest(test_convertToLux)
{
  fprintf(stderr, "VERSION: %s\n", MAX44009_LIB_VERSION);

  Max44009 LuxA(0x4A);

  assertEqualFloat(0.000, LuxA.convertToLux(0x00, 0x00), 0.0001);
  assertEqualFloat(0.045, LuxA.convertToLux(0x00, 0x01), 0.0001);
  assertEqualFloat(0.720, LuxA.convertToLux(0x01, 0x00), 0.0001);
  assertEqualFloat(1.530, LuxA.convertToLux(0x11, 0x01), 0.0001);
  fprintf(stderr, "\n");

  assertEqualFloat(187269, LuxA.convertToLux(0xEF, 0x0E), 1);
  assertEqualFloat(188006, LuxA.convertToLux(0xEF, 0x0F), 1);
  fprintf(stderr, "\ndone...\n");
}


unittest_main()

// --------
