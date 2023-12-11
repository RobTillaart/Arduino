//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-17
// PURPOSE: unit tests for the PCA9551 I2C LED driver
//          https://github.com/RobTillaart/PCA9551
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


#include "PCA9551.h"


unittest_setup()
{
  fprintf(stderr, "PCA9551_LIB_VERSION: %s\n", (char *) PCA9551_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  fprintf(stderr, "\nregisters");
  assertEqual(PCA9551_INPUT      , 0x00);
  assertEqual(PCA9551_PSC0       , 0x01);
  assertEqual(PCA9551_PWM0       , 0x02);
  assertEqual(PCA9551_PSC1       , 0x03);
  assertEqual(PCA9551_PWM1       , 0x04);
  assertEqual(PCA9551_LS0        , 0x05);

  fprintf(stderr, "\noutput modi");
  assertEqual(PCA9551_MODE_LOW   , 0x00);
  assertEqual(PCA9551_MODE_HIGH  , 0x01);
  assertEqual(PCA9551_MODE_PWM0  , 0x02);
  assertEqual(PCA9551_MODE_PWM1  , 0x03);

  fprintf(stderr, "\nerrorcodes");
  assertEqual(PCA9551_OK         , 0x00);
  assertEqual(PCA9551_ERROR      , 0xFF);
  assertEqual(PCA9551_ERR_WRITE  , 0xFE);
  assertEqual(PCA9551_ERR_CHAN   , 0xFD);
  assertEqual(PCA9551_ERR_MODE   , 0xFC);
  assertEqual(PCA9551_ERR_REG    , 0xFB);
  assertEqual(PCA9551_ERR_I2C    , 0xFA);
}


unittest(test_constructor)
{
  PCA9551 pca(0x62);

  Wire.begin();

  assertEqual(8, pca.outputCount());
  assertEqual(0x62, pca.getAddress());
}

//  need mock up for more tests.
//  low prio.

unittest_main()


//  -- END OF FILE --

