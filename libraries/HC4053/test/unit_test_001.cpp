//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-01-25
// PURPOSE: unit tests for the HC4053 sensor
//          https://github.com/RobTillaart/HC4067
//

// supported assertions
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


#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "HC4053.h"


unittest_setup()
{
    fprintf(stderr, "HC4053_LIB_VERSION: %s\n", (char *) HC4053_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_channel)
{
  HC4053 mp(3,4,5);

  mp.setChannelA(0);
  assertEqual(0, mp.getChannelA());
  mp.setChannelA(1);
  assertEqual(1, mp.getChannelA());

  mp.setChannelB(0);
  assertEqual(0, mp.getChannelB());
  mp.setChannelB(1);
  assertEqual(1, mp.getChannelB());

  mp.setChannelC(0);
  assertEqual(0, mp.getChannelC());
  mp.setChannelC(1);
  assertEqual(1, mp.getChannelC());
}


unittest(test_enable)
{
  HC4053 mp1(3,4,5);
  assertTrue(mp1.isEnabled());

  HC4053 mp2(3,4,5,6);
  assertFalse(mp2.isEnabled());

  mp2.enable();
  assertTrue(mp2.isEnabled());

  mp2.disable();
  assertFalse(mp2.isEnabled());
}


unittest_main()


//  -- END OF FILE --
