//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-01-09
// PURPOSE: unit tests for the TCA9554 library
//          https://github.com/RobTillaart/TCA9554
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
#include "TCA9554.h"


unittest_setup()
{
  fprintf(stderr, "TCA9554_LIB_VERSION:\t%s\n", (char *) TCA9554_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor_TCA9554)
{
  TCA9554 TCA(0x22);

  Wire.begin();

  assertTrue(TCA.begin());
  assertTrue(TCA.isConnected());
  assertEqual(54, TCA.getType());
}


unittest(test_constructor_TCA9534)
{
  TCA9534 TCA(0x22);

  Wire.begin();

  assertTrue(TCA.begin());
  assertTrue(TCA.isConnected());
  assertEqual(34, TCA.getType());
}


unittest(test_constants_I)
{
  assertEqual(0x00, TCA9554_OK);
  assertEqual(0x81, TCA9554_PIN_ERROR);
  assertEqual(0x82, TCA9554_I2C_ERROR);
  assertEqual(0x83, TCA9554_VALUE_ERROR);
  assertEqual(0x84, TCA9554_PORT_ERROR);
  assertEqual(-100, TCA9554_INVALID_READ);
}


unittest(test_constants_II)
{
  assertEqual(0,  TCA_P00);
  assertEqual(1,  TCA_P01);
  assertEqual(2,  TCA_P02);
  assertEqual(3,  TCA_P03);
  assertEqual(4,  TCA_P04);
  assertEqual(5,  TCA_P05);
  assertEqual(6,  TCA_P06);
  assertEqual(7,  TCA_P07);
}


unittest_main()


//  -- END OF FILE --

