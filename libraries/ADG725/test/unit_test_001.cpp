//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-24
// PURPOSE: unit tests for the ADG725 library
//          https://github.com/RobTillaart/ADG725
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
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
#include "ADG725.h"


unittest_setup()
{
  fprintf(stderr, "ADG725_LIB_VERSION: %s\n", (char *) ADG725_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  ADG725 ADG(10, 11, 12);

  assertEqual(16, ADG.channelCount());
  assertEqual(ADG725_ALLOFF, ADG.getChannelA());
  assertEqual(ADG725_ALLOFF, ADG.getChannelB());
}


unittest(test_constants)
{
  assertEqual(0x80, ADG725_ALLOFF );
  assertEqual(0x20, ADG725_A_ONLY );
  assertEqual(0x40, ADG725_B_ONLY );
  assertEqual(0x00, ADG725_AB_BOTH);
}


unittest(test_allOff)
{
  ADG725 ADG(10, 11, 12);

  ADG.setChannelA(13);
  ADG.setChannelB(7);
  ADG.allOff();
  assertEqual(ADG725_ALLOFF, ADG.getChannelA());
  assertEqual(ADG725_ALLOFF, ADG.getChannelB());
}


unittest(test_channel)
{
  ADG725 ADG(10, 11, 12);

  for (int ch = 0; ch < 16; ch++)
  {
    ADG.setChannel(ch);
    assertEqual(ch, ADG.getChannelA());
    assertEqual(ch, ADG.getChannelB());
  }
}


unittest(test_channelA)
{
  ADG725 ADG(10, 11, 12);

  ADG.setChannelB(7);
  for (int ch = 0; ch < 16; ch++)
  {
    ADG.setChannelA(ch);
    assertEqual(ch, ADG.getChannelA());
  }
  assertEqual(7, ADG.getChannelB());
}


unittest(test_channelB)
{
  ADG725 ADG(10, 11, 12);

  ADG.setChannelA(13);
  for (int ch = 0; ch < 16; ch++)
  {
    ADG.setChannelB(ch);
    assertEqual(ch, ADG.getChannelB());
  }
  assertEqual(13, ADG.getChannelA());
}


unittest_main()


//  -- END OF FILE --

