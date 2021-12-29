//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-09
// PURPOSE: unit tests for the Troolean three valued booleans
//          https://github.com/RobTillaart/Troolean
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
#include "Troolean.h"


unittest_setup()
{
  fprintf(stderr, "TROOLEAN_LIB_VERSION: %s\n", (char *) TROOLEAN_LIB_VERSION );
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  Troolean f(false);
  Troolean t(true);
  Troolean u(-1);
  Troolean v(u);
  
  // should not use these
  assertFalse(f);
  assertTrue(t);

  // use these
  assertTrue(f.isFalse());
  assertTrue(t.isTrue());
  assertTrue(u.isUnknown());
  assertTrue(v.isUnknown());

}


// TODO extend operators  comparison etc

unittest_main()

// --------
