//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-25
// PURPOSE: unit tests for the ADG726 library
//          https://github.com/RobTillaart/ADG726
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
#include "ADG726.h"


unittest_setup()
{
  fprintf(stderr, "ADG726_LIB_VERSION: %s\n", (char *) ADG726_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  uint8_t arr[4] = {4, 5, 6, 7};
  ADG726 ADG(arr, 10, 11, 12, 13);

  assertEqual(16, ADG.channelCount());
  assertEqual(ADG726_ALLOFF, ADG.getChannelA());
  assertEqual(ADG726_ALLOFF, ADG.getChannelB());
}


unittest(test_constants)
{
  assertEqual(0x80, ADG726_ALLOFF );
}


unittest(test_allOff)
{
  uint8_t arr[4] = {4, 5, 6, 7};
  ADG726 ADG(arr, 10, 11, 12, 13);

  ADG.setChannelA(13);
  ADG.setChannelB(7);
  ADG.allOff();
  assertEqual(ADG726_ALLOFF, ADG.getChannelA());
  assertEqual(ADG726_ALLOFF, ADG.getChannelB());
}


unittest(test_channel)
{
  uint8_t arr[4] = {4, 5, 6, 7};
  ADG726 ADG(arr, 10, 11, 12, 13);

  for (int ch = 0; ch < 16; ch++)
  {
    ADG.setChannel(ch);
    assertEqual(ch, ADG.getChannelA());
    assertEqual(ch, ADG.getChannelB());
  }
}


unittest(test_channelA)
{
  uint8_t arr[4] = {4, 5, 6, 7};
  ADG726 ADG(arr, 10, 11, 12, 13);

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
  uint8_t arr[4] = {4, 5, 6, 7};
  ADG726 ADG(arr, 10, 11, 12, 13);

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

