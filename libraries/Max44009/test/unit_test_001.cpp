//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-30
// PURPOSE: unit tests for the Max44009
//          https://github.com/RobTillaart/Max44009
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


#include "Max44009.h"


unittest_setup()
{
  fprintf(stderr, "MAX44009_LIB_VERSION: %s\n", (char *) MAX44009_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(MAX44009_DEFAULT_ADDRESS, 0x4A);
  assertEqual(MAX44009_ALT_ADDRESS    , 0x4B);

  assertEqual(MAX44009_INTERRUPT_STATUS  , 0x00);
  assertEqual(MAX44009_INTERRUPT_ENABLE  , 0x01);
  assertEqual(MAX44009_CONFIGURATION     , 0x02);
  assertEqual(MAX44009_LUX_READING_HIGH  , 0x03);
  assertEqual(MAX44009_LUX_READING_LOW   , 0x04);
  assertEqual(MAX44009_THRESHOLD_HIGH    , 0x05);
  assertEqual(MAX44009_THRESHOLD_LOW     , 0x06);
  assertEqual(MAX44009_THRESHOLD_TIMER   , 0x07);

  assertEqual(MAX44009_CFG_CONTINUOUS    , 0x80);
  assertEqual(MAX44009_CFG_MANUAL        , 0x40);
  assertEqual(MAX44009_CFG_CDR           , 0x08);
  assertEqual(MAX44009_CFG_TIMER         , 0x07);

  assertEqual(MAX44009_OK                , 0  );
  assertEqual(MAX44009_ERROR_WIRE_REQUEST, -10);
  assertEqual(MAX44009_ERROR_OVERFLOW    , -20);
  assertEqual(MAX44009_ERROR_HIGH_BYTE   , -30);
  assertEqual(MAX44009_ERROR_LOW_BYTE    , -31);
}


unittest(test_constructor)
{
  Max44009 LuxA(0x4A);
  Wire.begin();

  assertEqual(MAX44009_OK, LuxA.getError());
  assertTrue(LuxA.isConnected());   //  TODO should be false...

  //  TODO more tests if WIRE works...
}


unittest(test_convertToLux)
{
  Max44009 LuxA(0x4A);

  assertEqualFloat(0.000, LuxA.convertToLux(0x00, 0x00), 0.0001);
  assertEqualFloat(0.045, LuxA.convertToLux(0x00, 0x01), 0.0001);
  assertEqualFloat(0.720, LuxA.convertToLux(0x01, 0x00), 0.0001);
  assertEqualFloat(1.530, LuxA.convertToLux(0x11, 0x01), 0.0001);
  fprintf(stderr, "\n");

  assertEqualFloat(187269, LuxA.convertToLux(0xEF, 0x0E), 1);
  assertEqualFloat(188006, LuxA.convertToLux(0xEF, 0x0F), 1);
  fprintf(stderr, "\ndone...\n");
}


unittest_main()


//  -- END OF FILE --
