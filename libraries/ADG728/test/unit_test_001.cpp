//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2021-03-16
// PURPOSE: unit tests for the ADG728 I2C matrix switch. Multiplexer.
//          https://github.com/RobTillaart/ADG728
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

/*
  most unit tests will test for fail
  as there is no sensor connected
  and there is no mockup.

  It appears that Wire.write does not fail without sensor...
*/


#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "ADG728.h"


unittest_setup()
{
  fprintf(stderr, "ADG728_LIB_VERSION: %s\n", (char *) ADG728_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0,   ADG728_OK);
  assertEqual(-10, ADG728_ERROR_I2C);
  assertEqual(-20, ADG728_ERROR_CHANNEL);
}


unittest(test_constructor)
{
  ADG728 adg(0x4C);

  Wire.begin();

  assertTrue(adg.begin());
  assertTrue(adg.isConnected());
  assertEqual(8, adg.channelCount());
}


unittest(test_enable)
{
  ADG728 adg(0x4C);

  Wire.begin();

  bool b = adg.begin();
  assertEqual(b, true);

  uint8_t mask = 0x00;
  for (int chan = 0; chan < 8; chan++)
  {
    adg.enableChannel(chan);
    assertTrue(adg.isEnabled(chan));
  }
  assertEqual(0xFF, adg.getChannelMask());
  adg.setChannelMask(0x00);
  assertEqual(0x00, adg.getChannelMask());
}


unittest(test_select)
{
  ADG728 adg(0x4C);

  Wire.begin();

  bool b = adg.begin();
  assertEqual(b, true);

  uint8_t mask = 0x00;
  for (int chan = 0; chan < 8; chan++)
  {
    adg.selectChannel(chan);
    assertTrue(adg.isEnabled(chan));
  }
  assertEqual(0x80, adg.getChannelMask());
  adg.setChannelMask(0x00);
  assertEqual(0x00, adg.getChannelMask());
}


unittest_main()


//  -- END OF FILE --

