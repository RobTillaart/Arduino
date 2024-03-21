//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-25
// PURPOSE: unit tests for the ADG732 library
//          https://github.com/RobTillaart/ADG732
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


#include "ADG732.h"


unittest_setup()
{
  fprintf(stderr, "ADG732_LIB_VERSION: %s\n", (char *) ADG732_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  uint8_t arr[5] = {4, 5, 6, 7, 8};
  ADG732 ADG(arr, 10, 11, 12);

  assertEqual(32, ADG.channelCount());
  assertEqual(ADG732_ALLOFF, ADG.getChannel());
}


unittest(test_constants)
{
  assertEqual(0x80, ADG732_ALLOFF );
}


unittest(test_allOff)
{
  uint8_t arr[5] = {4, 5, 6, 7, 8};
  ADG732 ADG(arr, 10, 11, 12);

  ADG.setChannel(13);
  assertEqual(13, ADG.getChannel());
  ADG.allOff();
  assertEqual(ADG732_ALLOFF, ADG.getChannel());
}


unittest(test_channel)
{
  uint8_t arr[5] = {4, 5, 6, 7, 8};
  ADG732 ADG(arr, 10, 11, 12);

  for (int ch = 0; ch < 32; ch++)
  {
    ADG.setChannel(ch);
    assertEqual(ch, ADG.getChannel());
  }
}


unittest_main()


//  -- END OF FILE --

