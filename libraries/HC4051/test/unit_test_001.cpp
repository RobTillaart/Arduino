//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-01-25
// PURPOSE: unit tests for the HC4051 sensor
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
#include "HC4051.h"


unittest_setup()
{
    fprintf(stderr, "HC4051_LIB_VERSION: %s\n", (char *) HC4051_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_channel)
{
  HC4051 mp(3,4,5);

  for (int ch = 0; ch < 8; ch++)
  {
    mp.setChannel(ch);
    assertEqual(ch, mp.getChannel());
  }
}


unittest(test_enable)
{
  HC4051 mp1(3,4,5);
  assertTrue(mp1.isEnabled());

  HC4051 mp2(3,4,5,6);
  assertFalse(mp2.isEnabled());

  mp2.enable();
  assertTrue(mp2.isEnabled());

  mp2.disable();
  assertFalse(mp2.isEnabled());
}


unittest_main()


//  -- END OF FILE --
