//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-07
// PURPOSE: unit tests for the randomHelpers.h file
//          https://github.com/RobTillaart/randomHelpers
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
#include "randomHelpers.h"


unittest_setup()
{
  fprintf(stderr, "RANDOM_HELPERS_VERSION: %s\n", (char *) RANDOM_HELPERS_VERSION);
}


unittest_teardown()
{
}


unittest(test_all)
{
  for (int i = 0; i < 10; i ++)
  {
    fprintf(stderr, "\n round %d\n", i);
    assertMore(2,          getRandom1());
    assertMore(4,          getRandom2());
    assertMore(8,          getRandom3());
    assertMore(16,         getRandom4());
    assertMore(32,         getRandom5());
    assertMore(64,         getRandom6());
    assertMore(128,        getRandom7());
    assertMore(256,        getRandom8());
    assertMore(65536,      getRandom16());
    assertMore(16777216,   getRandom24());
    assertMore(pow(2, 32), getRandom32());
  }
}


unittest_main()


//  -- END OF FILE --

