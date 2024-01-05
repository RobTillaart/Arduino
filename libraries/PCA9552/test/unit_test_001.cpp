//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-17
// PURPOSE: unit tests for the PCA9552 I2C LED driver
//          https://github.com/RobTillaart/PCA9552
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


#include "PCA9552.h"


unittest_setup()
{
  fprintf(stderr, "PCA9552_LIB_VERSION: %s\n", (char *) PCA9552_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  fprintf(stderr, "\n registers");
  assertEqual(PCA9552_INPUT0     , 0x00);
  assertEqual(PCA9552_INPUT1     , 0x01);
  assertEqual(PCA9552_PSC0       , 0x02);
  assertEqual(PCA9552_PWM0       , 0x03);
  assertEqual(PCA9552_PSC1       , 0x04);
  assertEqual(PCA9552_PWM1       , 0x05);
  assertEqual(PCA9552_LS0        , 0x06);
  assertEqual(PCA9552_LS1        , 0x07);
  assertEqual(PCA9552_LS2        , 0x08);
  assertEqual(PCA9552_LS3        , 0x09);

  fprintf(stderr, "\n output modi");
  assertEqual(PCA9552_MODE_LOW   , 0x00);
  assertEqual(PCA9552_MODE_HIGH  , 0x01);
  assertEqual(PCA9552_MODE_PWM0  , 0x02);
  assertEqual(PCA9552_MODE_PWM1  , 0x03);

  fprintf(stderr, "\n error codes");
  assertEqual(PCA9552_OK         , 0x00);
  assertEqual(PCA9552_ERROR      , 0xFF);
  assertEqual(PCA9552_ERR_WRITE  , 0xFE);
  assertEqual(PCA9552_ERR_CHAN   , 0xFD);
  assertEqual(PCA9552_ERR_MODE   , 0xFC);
  assertEqual(PCA9552_ERR_REG    , 0xFB);
  assertEqual(PCA9552_ERR_I2C    , 0xFA);
}


unittest(test_constructor)
{
  PCA9552 pca(0x62);

  Wire.begin();

  assertEqual(16, pca.outputCount());
  assertEqual(0x62, pca.getAddress());
}

//  need mock up for more tests.
//  low prio.

unittest_main()


//  -- END OF FILE --

