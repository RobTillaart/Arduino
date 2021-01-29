//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-05
// PURPOSE: unit tests for the PinOutGroup
//          https://github.com/RobTillaart/PinOutGroup
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
#include "PinOutGroup.h"


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_all)
{
  fprintf(stderr, "VERSION: %s\n", PINOUTGROUP_LIB_VERSION);

  PinOutGroup POG;
  uint8_t ar[46] = {2, 3, 4, 5, 6, 7};
  
  assertEqual(0, POG.size());
  assertEqual(16, POG.available());
  assertFalse(POG.isInGroup(2));

  POG.add(6, ar, LOW);
  assertEqual(6, POG.size());
  assertEqual(10, POG.available());
}

unittest_main()

// --------
