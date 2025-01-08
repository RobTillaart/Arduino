//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-01
// PURPOSE: unit tests for the I2C DAC8574 library
//          https://github.com/RobTillaart/DAC8574
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


#include "DAC8574.h"


unittest_setup()
{
  fprintf(stderr, "DAC8574_LIB_VERSION: %s\n", (char *) DAC8574_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(DAC8574_OK           , 0x00);
  assertEqual(DAC8574_I2C_ERROR    , 0x81);
  assertEqual(DAC8574_ADDRESS_ERROR, 0x82);
  assertEqual(DAC8574_BUFFER_ERROR,  0x83);
  assertEqual(DAC8574_CHANNEL_ERROR, 0x84);

  assertEqual(DAC8574_MODE_STORE_CACHE, 0x00);
  assertEqual(DAC8574_MODE_NORMAL     , 0x01);
  assertEqual(DAC8574_MODE_WRITE_CACHE, 0x02);
  assertEqual(DAC8574_MODE_BRCAST_0   , 0x03);
  assertEqual(DAC8574_MODE_BRCAST_1   , 0x04);
  assertEqual(DAC8574_MODE_BRCAST_2   , 0x05);
}


unittest(test_constructor)
{
  DAC8574 dev(0x4C);

  Wire.begin();

  assertTrue(dev.begin());
  assertTrue(dev.isConnected());

  assertEqual(0x4C, dev.getAddress());

  //  defaults
  assertEqual(0, dev.lastWrite(0));
  assertEqual(DAC8574_OK, dev.lastError());
  assertEqual(DAC8574_MODE_NORMAL, dev.getWriteMode());
  assertEqual(0x00, dev.getExtendedAddress());
}


unittest(test_setWriteMode)
{
  DAC8574 dev(0x4C);

  Wire.begin();
  assertTrue(dev.begin());

  assertTrue(dev.isConnected());
  //  default
  assertEqual(DAC8574_MODE_NORMAL, dev.getWriteMode());

  dev.setWriteMode(DAC8574_MODE_STORE_CACHE);
  assertEqual(DAC8574_MODE_STORE_CACHE, dev.getWriteMode());

  dev.setWriteMode(DAC8574_MODE_NORMAL);
  assertEqual(DAC8574_MODE_NORMAL, dev.getWriteMode());

  dev.setWriteMode(DAC8574_MODE_WRITE_CACHE);
  assertEqual(DAC8574_MODE_WRITE_CACHE, dev.getWriteMode());
}


unittest(test_setExtendedAddress)
{
  DAC8574 dev(0x4C);

  Wire.begin();
  assertTrue(dev.begin());

  assertTrue(dev.isConnected());
  //  default
  assertEqual(0x00, dev.getExtendedAddress());
  //  valid
  for (int a2a3 = 0; a2a3 < 4; a2a3++)
  {
    assertTrue(dev.setExtendedAddress(a2a3));
    assertEqual(a2a3, dev.getExtendedAddress());
  }
  //  invalid
  assertFalse(dev.setExtendedAddress(0x04));
}


unittest_main()


//  -- END OF FILE --

