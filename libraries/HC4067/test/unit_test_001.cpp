//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-01-25
// PURPOSE: unit tests for the HC4067 sensor
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
#include "HC4067.h"


unittest_setup()
{
    fprintf(stderr, "HC4067_LIB_VERSION: %s\n", (char *) HC4067_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_channel)
{
  HC4067 mp(3,4,5,6,7);

  for (int ch = 0; ch < 16; ch++)
  {
    mp.setChannel(ch);
    assertEqual(ch, mp.getChannel());
  }
}


unittest(test_enable)
{
  HC4067 mp1(3,4,5,6);
  assertTrue(mp1.isEnabled());

  HC4067 mp2(3,4,5,6,7);
  assertFalse(mp2.isEnabled());

  mp2.enable();
  assertTrue(mp2.isEnabled());

  mp2.disable();
  assertFalse(mp2.isEnabled());
}


unittest_main()


//  -- END OF FILE --
