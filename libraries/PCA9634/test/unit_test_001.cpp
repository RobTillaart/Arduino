//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-01-03
// PURPOSE: unit tests for the PCA9634 I2C LED driver
//          https://github.com/RobTillaart/PCA9634
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


#include "PCA9634.h"


unittest_setup()
{
  fprintf(stderr, "PCA9634_LIB_VERSION: %s\n", (char *) PCA9634_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(PCA9634_MODE1      , 0x00);
  assertEqual(PCA9634_MODE2      , 0x01);

  assertEqual(PCA9634_GRPPWM     , 0x0A);
  assertEqual(PCA9634_GRPFREQ    , 0x0B);
  assertEqual(PCA9634_LEDOUT_BASE, 0x0C);

  assertEqual(PCA9634_LEDOFF     , 0x00);
  assertEqual(PCA9634_LEDON      , 0x01);
  assertEqual(PCA9634_LEDPWM     , 0x02);
  assertEqual(PCA9634_LEDGRPPWM  , 0x03);

  fprintf(stderr, "\nerrorcodes");
  assertEqual(PCA9634_OK         , 0x00);
  assertEqual(PCA9634_ERROR      , 0xFF);
  assertEqual(PCA9634_ERR_WRITE  , 0xFE);
  assertEqual(PCA9634_ERR_CHAN   , 0xFD);
  assertEqual(PCA9634_ERR_MODE   , 0xFC);
  assertEqual(PCA9634_ERR_REG    , 0xFB);
  assertEqual(PCA9634_ERR_I2C    , 0xFA);
}


unittest(test_constructor)
{
  PCA9634 ledArray(0x20);
  assertTrue(ledArray.begin());
  assertTrue(ledArray.isConnected());
  assertEqual(8, ledArray.channelCount());
}


unittest(test_LedDriverMode)
{
  PCA9634 ledArray(0x20);
  assertTrue(ledArray.begin());

  // TODO
}


unittest_main()

// --------
