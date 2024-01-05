//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-01
// PURPOSE: unit tests for the Optoma library
//          https://github.com/RobTillaart/Optoma
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
#include "optoma.h"


unittest_setup()
{
  fprintf(stderr, "OPTOMA_LIB_VERSION: %s\n", (char *) OPTOMA_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  Optoma beamer;

  beamer.init(22);
  assertEqual(9600, beamer.getBaudrate());

  // todo godmode ?
  beamer.switchOn();
  assertTrue(beamer.isOn());
  beamer.switchOff();
  assertFalse(beamer.isOn());
}


unittest_main()


//  -- END OF FILE --

