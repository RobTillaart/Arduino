//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-06-09
// PURPOSE: unit tests for the TCA9555 library
//          https://github.com/RobTillaart/TCA9555
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
#include "TCA9555.h"


unittest_setup()
{
  fprintf(stderr, "TCA9555_LIB_VERSION:\t%s\n", (char *) TCA9555_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor_TCA9555)
{
  TCA9555 TCA(0x22);

  Wire.begin();

  assertTrue(TCA.begin());
  assertTrue(TCA.isConnected());
  assertEqual(55, TCA.getType());
}


unittest(test_constructor_TCA9535)
{
  TCA9535 TCA(0x22);

  Wire.begin();

  assertTrue(TCA.begin());
  assertTrue(TCA.isConnected());
  assertEqual(35, TCA.getType());
}


unittest(test_constants_I)
{
  assertEqual(0x00, TCA9555_OK);
  assertEqual(0x81, TCA9555_PIN_ERROR);
  assertEqual(0x82, TCA9555_I2C_ERROR);
  assertEqual(0x83, TCA9555_VALUE_ERROR);
  assertEqual(0x84, TCA9555_PORT_ERROR);
  assertEqual(-100, TCA9555_INVALID_READ);
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
  assertEqual(8,  TCA_P10);
  assertEqual(9,  TCA_P11);
  assertEqual(10, TCA_P12);
  assertEqual(11, TCA_P13);
  assertEqual(12, TCA_P14);
  assertEqual(13, TCA_P15);
  assertEqual(14, TCA_P16);
  assertEqual(15, TCA_P17);
}


unittest_main()


//  -- END OF FILE --

