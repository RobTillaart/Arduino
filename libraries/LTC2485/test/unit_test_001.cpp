//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-21
// PURPOSE: unit tests for the LTC2485 library
//          https://github.com/RobTillaart/LTC2485
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


#include "LTC2485.h"



unittest_setup()
{
  fprintf(stderr, "LTC2485_LIB_VERSION: %s\n", (char *) LTC2485_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  //  CONFIG CONSTANTS
  assertEqual(LTC2485_SPEED_1X       , 0x00);
  assertEqual(LTC2485_SPEED_2X       , 0x01);
  assertEqual(LTC2485_REJECT_50HZ    , 0x02);
  assertEqual(LTC2485_REJECT_60HZ    , 0x04);
  assertEqual(LTC2485_REJECT_50_60_HZ, 0x00);
  assertEqual(LTC2485_INTERNAL_TEMP  , 0x08);

  //  ERROR CONSTANTS
  assertEqual(LTC2485_OK             , 0 );
  assertEqual(LTC2485_ERR_CONFIG_ADC , -1);
  assertEqual(LTC2485_ERR_CONFIG_TEMP, -2);
  assertEqual(LTC2485_ERR_I2C_W      , -3);
  assertEqual(LTC2485_ERR_I2C_R      , -4);
}


unittest(test_constructor)
{
  LTC2485 LTC(0x14);  //  all address lines GND

  assertEqual(0x14, LTC.getAddress());
}


unittest_main()


//  -- END OF FILE --

