//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-30
// PURPOSE: unit tests for the Max44007
//          https://github.com/RobTillaart/Max44007
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


#include "Max44007.h"


unittest_setup()
{
  fprintf(stderr, "MAX44007_LIB_VERSION: %s\n", (char *) MAX44007_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(MAX44007_DEFAULT_ADDRESS, 0x5A);
  assertEqual(MAX44007_ALT_ADDRESS    , 0x5B);

  assertEqual(MAX44007_INTERRUPT_STATUS  , 0x00);
  assertEqual(MAX44007_INTERRUPT_ENABLE  , 0x01);
  assertEqual(MAX44007_CONFIGURATION     , 0x02);
  assertEqual(MAX44007_LUX_READING_HIGH  , 0x03);
  assertEqual(MAX44007_LUX_READING_LOW   , 0x04);
  assertEqual(MAX44007_THRESHOLD_HIGH    , 0x05);
  assertEqual(MAX44007_THRESHOLD_LOW     , 0x06);
  assertEqual(MAX44007_THRESHOLD_TIMER   , 0x07);

  assertEqual(MAX44007_CFG_CONTINUOUS    , 0x80);
  assertEqual(MAX44007_CFG_MANUAL        , 0x40);
  assertEqual(MAX44007_CFG_CDR           , 0x08);
  assertEqual(MAX44007_CFG_TIMER         , 0x07);

  assertEqual(MAX44007_OK                , 0  );
  assertEqual(MAX44007_ERROR_WIRE_REQUEST, -10);
  assertEqual(MAX44007_ERROR_OVERFLOW    , -20);
  assertEqual(MAX44007_ERROR_HIGH_BYTE   , -30);
  assertEqual(MAX44007_ERROR_LOW_BYTE    , -31);
}


unittest(test_constructor)
{
  Max44007 LuxA(0x5A);
  Wire.begin();

  assertEqual(MAX44007_OK, LuxA.getError());
  assertTrue(LuxA.isConnected());   //  TODO should be false...

  //  TODO more tests if WIRE works...
}


unittest(test_convertToLux)
{
  Max44007 LuxA(0x5A);

  assertEqualFloat(0.000, LuxA.convertToLux(0x00, 0x00), 0.0001);
  assertEqualFloat(0.025, LuxA.convertToLux(0x00, 0x01), 0.0001);
  assertEqualFloat(0.400, LuxA.convertToLux(0x01, 0x00), 0.0001);
  assertEqualFloat(0.850, LuxA.convertToLux(0x11, 0x01), 0.0001);
  fprintf(stderr, "\n");

  assertEqualFloat(104038, LuxA.convertToLux(0xEF, 0x0E), 1);
  assertEqualFloat(104448, LuxA.convertToLux(0xEF, 0x0F), 1);
  fprintf(stderr, "\ndone...\n");
}


unittest_main()


//  -- END OF FILE --
