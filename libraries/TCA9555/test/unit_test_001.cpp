//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-06-09
// PURPOSE: unit tests for the TCA9555 library
//          https://github.com/RobTillaart/TCA9555
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
#include "TCA9555.h"


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  fprintf(stderr, "TCA9555_LIB_VERSION:\t%s\n", TCA9555_LIB_VERSION);
  TCA9555 TCA(0x22);

  assertTrue(TCA.begin());
  assertTrue(TCA.isConnected());
}


unittest(test_constants)
{
  assertEqual(0x00, TCA9555_OK);
  assertEqual(0x81, TCA9555_PIN_ERROR);
  assertEqual(0x82, TCA9555_I2C_ERROR);
  assertEqual(0x83, TCA9555_VALUE_ERROR);
  assertEqual(0x84, TCA9555_PORT_ERROR);
  assertEqual(-100, TCA9555_INVALID_READ);
}


unittest_main()

// --------
