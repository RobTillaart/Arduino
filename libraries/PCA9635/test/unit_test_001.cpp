//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-01
// PURPOSE: unit tests for the PCA9635 I2C LED driver
//          https://github.com/RobTillaart/PCA9635
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


#include "PCA9635.h"


unittest_setup()
{
  fprintf(stderr, "PCA9635_LIB_VERSION: %s\n", (char *) PCA9635_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(PCA9635_MODE1      , 0x00);
  assertEqual(PCA9635_MODE2      , 0x01);

  assertEqual(PCA9635_GRPPWM     , 0x12);
  assertEqual(PCA9635_GRPFREQ    , 0x13);
  assertEqual(PCA9635_LEDOUT_BASE, 0x14);

  assertEqual(PCA9635_LEDOFF     , 0x00);
  assertEqual(PCA9635_LEDON      , 0x01);
  assertEqual(PCA9635_LEDPWM     , 0x02);
  assertEqual(PCA9635_LEDGRPPWM  , 0x03);

  fprintf(stderr, "\nerrorcodes");
  assertEqual(PCA9635_OK         , 0x00);
  assertEqual(PCA9635_ERROR      , 0xFF);
  assertEqual(PCA9635_ERR_WRITE  , 0xFE);
  assertEqual(PCA9635_ERR_CHAN   , 0xFD);
  assertEqual(PCA9635_ERR_MODE   , 0xFC);
  assertEqual(PCA9635_ERR_REG    , 0xFB);
  assertEqual(PCA9635_ERR_I2C    , 0xFA);
}


unittest(test_constructor)
{
  PCA9635 ledArray(0x20);
  assertTrue(ledArray.begin());
  assertTrue(ledArray.isConnected());
  assertEqual(16, ledArray.channelCount());
}


unittest(test_LedDriverMode)
{
  PCA9635 ledArray(0x20);
  assertTrue(ledArray.begin());

  // TODO
}


unittest_main()

// --------
