//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-16
// PURPOSE: unit tests for the PCA9553 I2C LED driver
//          https://github.com/RobTillaart/PCA9553
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


#include "PCA9553.h"


unittest_setup()
{
  fprintf(stderr, "PCA9553_LIB_VERSION: %s\n", (char *) PCA9553_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  fprintf(stderr, "\nregisters");
  assertEqual(PCA9553_INPUT      , 0x00);
  assertEqual(PCA9553_PSC0       , 0x01);
  assertEqual(PCA9553_PWM0       , 0x02);
  assertEqual(PCA9553_PSC1       , 0x03);
  assertEqual(PCA9553_PWM1       , 0x04);
  assertEqual(PCA9553_LS0        , 0x05);

  fprintf(stderr, "\noutput modi");
  assertEqual(PCA9553_MODE_LOW   , 0x00);
  assertEqual(PCA9553_MODE_HIGH  , 0x01);
  assertEqual(PCA9553_MODE_PWM0  , 0x02);
  assertEqual(PCA9553_MODE_PWM1  , 0x03);

  fprintf(stderr, "\nerrorcodes");
  assertEqual(PCA9553_OK         , 0x00);
  assertEqual(PCA9553_ERROR      , 0xFF);
  assertEqual(PCA9553_ERR_WRITE  , 0xFE);
  assertEqual(PCA9553_ERR_CHAN   , 0xFD);
  assertEqual(PCA9553_ERR_MODE   , 0xFC);
  assertEqual(PCA9553_ERR_REG    , 0xFB);
  assertEqual(PCA9553_ERR_I2C    , 0xFA);
}


unittest(test_constructor)
{
  PCA9553 pca(0x62);

  Wire.begin();

  assertEqual(4, pca.outputCount());
  assertEqual(0x62, pca.getAddress());
}

//  need mock up for more tests.
//  low prio.

unittest_main()


//  -- END OF FILE --

