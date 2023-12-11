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
  fprintf(stderr, "\nregisters");
  assertEqual(PCA963X_MODE1      , 0x00);
  assertEqual(PCA963X_MODE2      , 0x01);

  assertEqual(PCA963X_PWM(0)     , 0x82);
  assertEqual(PCA963X_PWM(1)     , 0x83);
  assertEqual(PCA963X_GRPPWM     , 0x12);
  assertEqual(PCA963X_GRPFREQ    , 0x13);
  assertEqual(PCA963X_LEDOUT_BASE, 0x14);

  assertEqual(PCA963X_LEDOFF     , 0x00);
  assertEqual(PCA963X_LEDON      , 0x01);
  assertEqual(PCA963X_LEDPWM     , 0x02);
  assertEqual(PCA963X_LEDGRPPWM  , 0x03);

  fprintf(stderr, "\nerrorcodes");
  assertEqual(PCA963X_OK         , 0x00);
  assertEqual(PCA963X_ERROR      , 0xFF);
  assertEqual(PCA963X_ERR_WRITE  , 0xFE);
  assertEqual(PCA963X_ERR_CHAN   , 0xFD);
  assertEqual(PCA963X_ERR_MODE   , 0xFC);
  assertEqual(PCA963X_ERR_REG    , 0xFB);
  assertEqual(PCA963X_ERR_I2C    , 0xFA);
}


unittest(test_constructor)
{
  PCA9635 ledArray(0x20);

  Wire.begin();

  assertTrue(ledArray.begin());
  assertTrue(ledArray.isConnected());
  assertEqual(16, ledArray.channelCount());
}


unittest(test_LedDriverMode)
{
  PCA9635 ledArray(0x20);

  Wire.begin();

  assertTrue(ledArray.begin());

  //  TODO
}


unittest(test_OutputEnable)
{
  PCA9635 ledArray(0x20);

  Wire.begin();

  assertTrue(ledArray.begin());

  assertEqual(HIGH, ledArray.getOutputEnable());

  assertTrue(ledArray.setOutputEnablePin(12));
  //  assertEqual(HIGH, ledArray.getOutputEnable());  //  need mock

  assertTrue(ledArray.setOutputEnable(true));
  //  assertEqual(LOW, ledArray.getOutputEnable());

  assertTrue(ledArray.setOutputEnable(false));
  //  assertEqual(HIGH, ledArray.getOutputEnable());

  assertTrue(ledArray.setOutputEnable(true));
  //  assertEqual(LOW, ledArray.getOutputEnable());

  assertFalse(ledArray.setOutputEnablePin(255));
  //  assertEqual(HIGH, ledArray.getOutputEnable());
}


unittest_main()


//  -- END OF FILE --

