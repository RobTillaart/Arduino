//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-06
// PURPOSE: unit tests for the Prandom
//          https://github.com/RobTillaart/Prandom
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
#include "Prandom.h"


unittest_setup()
{
  fprintf(stderr, "PRANDOM_LIB_VERSION: %s\n", (char *) PRANDOM_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  Prandom R;

  //  three seed() calls are possible
  R.seed();
  R.seed(42);
  R.seed(355, 113);

  assertLessOrEqual(100, R.randrange(100, 200));
  assertMoreOrEqual(200, R.randrange(100, 200));

  for (int bits = 0; bits < 32; bits++)
  {
    fprintf(stderr, "%d\t", bits);
    assertMoreOrEqual(pow(2, bits), R.getrandbits(bits));
  }

}


unittest_main()

// --------
