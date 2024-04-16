//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-01
// PURPOSE: unit tests for the I2C DAC8571 library
//          https://github.com/RobTillaart/DAC8571
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


#include "DAC8571.h"


unittest_setup()
{
  fprintf(stderr, "DAC8571_LIB_VERSION: %s\n", (char *) DAC8571_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(DAC8571_OK           , 0x00);
  assertEqual(DAC8571_I2C_ERROR    , 0x81);
  assertEqual(DAC8571_ADDRESS_ERROR, 0x82);
  
  assertEqual(DAC8571_MODE_STORE_CACHE, 0x00);
  assertEqual(DAC8571_MODE_NORMAL     , 0x01);
  assertEqual(DAC8571_MODE_WRITE_CACHE, 0x02);
  assertEqual(DAC8571_MODE_BRCAST_0   , 0x03);
  assertEqual(DAC8571_MODE_BRCAST_1   , 0x04);
  assertEqual(DAC8571_MODE_BRCAST_2   , 0x05);
}


unittest(test_constructor)
{
  DAC8571 dev(0x4C);

  Wire.begin();

  assertTrue(dev.begin());

  assertTrue(dev.isConnected());
  assertEqual(0, dev.lastWrite());
  assertEqual(DAC8571_OK, dev.lastError());
}


unittest_main()


//  -- END OF FILE --

