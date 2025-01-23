//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-05-18
// PURPOSE: unit tests for the INA229 library
//          https://github.com/RobTillaart/INA229
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


#include "INA229.h"



unittest_setup()
{
  fprintf(stderr, "\n INA229_LIB_VERSION: %s\n", (char *) INA229_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constructor)
{
INA229 INA(5, &SPI);

  assertTrue(INA.begin());
}


unittest(test_mode_enum)
{
  assertEqual(INA229_MODE_SHUTDOWN           , 0x00);
  assertEqual(INA229_MODE_TRIG_BUS           , 0x01);
  assertEqual(INA229_MODE_TRIG_SHUNT         , 0x02);
  assertEqual(INA229_MODE_TRIG_BUS_SHUNT     , 0x03);
  assertEqual(INA229_MODE_TRIG_TEMP          , 0x04);
  assertEqual(INA229_MODE_TRIG_TEMP_BUS      , 0x05);
  assertEqual(INA229_MODE_TRIG_TEMP_SHUNT    , 0x06);
  assertEqual(INA229_MODE_TRIG_TEMP_BUS_SHUNT, 0x07);
  assertEqual(INA229_MODE_SHUTDOWN2          , 0x08);
  assertEqual(INA229_MODE_CONT_BUS           , 0x09);
  assertEqual(INA229_MODE_CONT_SHUNT         , 0x0A);
  assertEqual(INA229_MODE_CONT_BUS_SHUNT     , 0x0B);
  assertEqual(INA229_MODE_CONT_TEMP          , 0x0C);
  assertEqual(INA229_MODE_CONT_TEMP_BUS      , 0x0D);
  assertEqual(INA229_MODE_CONT_TEMP_SHUNT    , 0x0E);
  assertEqual(INA229_MODE_CONT_TEMP_BUS_SHUNT, 0x0F);
}


unittest(test_average_enum)
{
  assertEqual(INA229_1_SAMPLE    , 0);
  assertEqual(INA229_4_SAMPLES   , 1);
  assertEqual(INA229_16_SAMPLES  , 2);
  assertEqual(INA229_64_SAMPLES  , 3);
  assertEqual(INA229_128_SAMPLES , 4);
  assertEqual(INA229_256_SAMPLES , 5);
  assertEqual(INA229_512_SAMPLES , 6);
  assertEqual(INA229_1024_SAMPLES, 7);
}


unittest(test_timing_enum)
{
  assertEqual(INA229_50_us  , 0);
  assertEqual(INA229_84_us  , 1);
  assertEqual(INA229_150_us , 2);
  assertEqual(INA229_280_us , 3);
  assertEqual(INA229_540_us , 4);
  assertEqual(INA229_1052_us, 5);
  assertEqual(INA229_2074_us, 6);
  assertEqual(INA229_4120_us, 7);
}


unittest(test_diag_enum)
{
  assertEqual(INA229_DIAG_MEMORY_STATUS    , 0);
  assertEqual(INA229_DIAG_CONVERT_COMPLETE , 1);
  assertEqual(INA229_DIAG_POWER_OVER_LIMIT , 2);
  assertEqual(INA229_DIAG_BUS_UNDER_LIMIT  , 3);
  assertEqual(INA229_DIAG_BUS_OVER_LIMIT   , 4);
  assertEqual(INA229_DIAG_SHUNT_UNDER_LIMIT, 5);
  assertEqual(INA229_DIAG_SHUNT_OVER_LIMIT , 6);
  assertEqual(INA229_DIAG_TEMP_OVER_LIMIT  , 7);
  assertEqual(INA229_DIAG_RESERVED         , 8);
  assertEqual(INA229_DIAG_MATH_OVERFLOW    , 9);
  assertEqual(INA229_DIAG_CHARGE_OVERFLOW  , 10);
  assertEqual(INA229_DIAG_ENERGY_OVERFLOW  , 11);
  assertEqual(INA229_DIAG_ALERT_POLARITY   , 12);
  assertEqual(INA229_DIAG_SLOW_ALERT       , 13);
  assertEqual(INA229_DIAG_CONVERT_READY    , 14);
  assertEqual(INA229_DIAG_ALERT_LATCH      , 15);
}



unittest_main()


//  -- END OF FILE --

