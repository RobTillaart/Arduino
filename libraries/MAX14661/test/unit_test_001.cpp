//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2021-06-02
// PURPOSE: unit tests for the MAX14661 multiplexer
//          https://github.com/RobTillaart/MAX14661
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
#include "MAX14661.h"


unittest_setup()
{
  fprintf(stderr, "MAX14661_LIB_VERSION: %s\n", (char *) MAX14661_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  //  error constants
  assertEqual(0x00, MAX14661_OK);
  assertEqual(0x80, MAX14661_ERR_I2C);
  assertEqual(0x81, MAX14661_ERR_CHANNEL);
}


unittest(test_constructor)
{
  MAX14661 MUX(0x4C);

  Wire.begin();

  assertEqual(MAX14661_OK, MUX.lastError());

  MUX.begin();
  assertEqual(MAX14661_OK, MUX.lastError());
}


unittest(test_channel_out_Of_range)
{
  MAX14661 MUX(0x4C);

  Wire.begin();
  MUX.begin();

  assertFalse(MUX.openChannel(16));
  assertFalse(MUX.closeChannel(16));
  assertFalse(MUX.isOpenChannel(16));

  assertFalse(MUX.openShadowChannelA(16));
  assertFalse(MUX.openShadowChannelA(16));
  assertFalse(MUX.isOpenShadowChannelA(16));

  assertFalse(MUX.openShadowChannelB(16));
  assertFalse(MUX.openShadowChannelB(16));
  assertFalse(MUX.isOpenShadowChannelB(16));

  assertFalse(MUX.openA(16));
  assertFalse(MUX.openB(16));
  assertFalse(MUX.closeA(16));
  assertFalse(MUX.closeB(16));
}


unittest_main()


//  -- END OF FILE --

