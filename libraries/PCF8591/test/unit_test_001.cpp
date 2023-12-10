//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-01
// PURPOSE: unit tests for the I2C PCF8591 library
//          https://github.com/RobTillaart/PCF8591
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
#include "PCF8591.h"


unittest_setup()
{
  fprintf(stderr, "PCF8591_LIB_VERSION: %s\n", (char *) PCF8591_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(PCF8591_OK           , 0x00);
  assertEqual(PCF8591_PIN_ERROR    , 0x81);
  assertEqual(PCF8591_I2C_ERROR    , 0x82);
  assertEqual(PCF8591_MODE_ERROR   , 0x83);
  assertEqual(PCF8591_CHANNEL_ERROR, 0x84);
  assertEqual(PCF8591_ADDRESS_ERROR, 0x85);
}


unittest(test_constructor)
{
  PCF8591 dev(0x48);

  Wire.begin();

  assertTrue(dev.begin());

  assertTrue(dev.isConnected());
  assertEqual(0, dev.lastWrite());
  assertEqual(PCF8591_OK, dev.lastError());
}


unittest(test_ADC_INCR)
{
  PCF8591 dev(0x48);

  Wire.begin();
  assertTrue(dev.begin());

  assertFalse(dev.isINCREnabled());
  dev.enableINCR();
  assertTrue(dev.isINCREnabled());
  dev.disableINCR();
  assertFalse(dev.isINCREnabled());
}


unittest(test_DAC)
{
  PCF8591 dev(0x48);

  Wire.begin();
  assertTrue(dev.begin());

  assertFalse(dev.isDACEnabled());
  dev.enableDAC();
  assertTrue(dev.isDACEnabled());
  dev.disableDAC();
  assertFalse(dev.isDACEnabled());
}


unittest_main()


//  -- END OF FILE --

