//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-05
// PURPOSE: unit tests for the I2C PCA9685 16 channel PWM
//          https://github.com/RobTillaart/PCA9685
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

#include "PCA9685.h"


unittest_setup()
{
  fprintf(stderr, "PCA9685_LIB_VERSION: %s\n", (char *) PCA9685_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(PCA9685_OK         , 0x00);
  assertEqual(PCA9685_ERROR      , 0xFF);
  assertEqual(PCA9685_ERR_CHANNEL, 0xFE);
  assertEqual(PCA9685_ERR_MODE   , 0xFD);
  assertEqual(PCA9685_ERR_I2C    , 0xFC);
}


unittest(test_constructor)
{
  PCA9685 ledArray(0x20);
  assertTrue(ledArray.begin());
  assertTrue(ledArray.isConnected());
}


unittest(test_TODO)
{
  PCA9685 ledArray(0x20);
  assertTrue(ledArray.begin());

  // TODO
}


unittest_main()

// --------
