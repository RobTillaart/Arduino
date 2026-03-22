//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-03-14
// PURPOSE: unit tests for the AMC1302 library
//     URL: https://github.com/RobTillaart/AMC1302
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)
// assertNotNull(actual)

#include <ArduinoUnitTests.h>


#include "Arduino.h"
#include "AMC1302.h"


unittest_setup()
{
  fprintf(stderr, "AMC1302_LIB_VERSION: %s\n", (char *) AMC1302_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0, AMC1302_OK);

  assertEqualFloat(AMC_FF_SINUS    , (1.0/sqrt(2)), 0.01);
  assertEqualFloat(AMC_FF_SQUARE   , (1.0)        , 0.01);
  assertEqualFloat(AMC_FF_TRIANGLE , (1.0/sqrt(3)), 0.01);
  assertEqualFloat(AMC_FF_SAWTOOTH , (1.0/sqrt(3)), 0.01);
  assertEqualFloat(AMC_DEFAULT_FREQ, (50.0)       , 0.01);
}


unittest(test_constructor)
{
  AMC1200 amc_1200(14, 15);
  AMC1300 amc00(14, 15);
  AMC1301 amc01(14, 15);
  AMC1302 amc02(14, 15);
  AMC1311 amc11(14, 15);
  AMC1351 amc51(14, 15);

  assertEqualFloat(amc_1200.getGain(), 8.0, 0.01);

  assertEqualFloat(amc00.getGain(), 8.2, 0.01);
  assertEqualFloat(amc01.getGain(), 8.2, 0.01);
  assertEqualFloat(amc02.getGain(),  41, 0.01);
  assertEqualFloat(amc11.getGain(), 1.0, 0.01);
  assertEqualFloat(amc51.getGain(), 0.4, 0.01);
}


unittest_main()


//  -- END OF FILE --

