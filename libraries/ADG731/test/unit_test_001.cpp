//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-24
// PURPOSE: unit tests for the ADG731 library
//          https://github.com/RobTillaart/ADG731
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


#include "ADG731.h"


unittest_setup()
{
  fprintf(stderr, "ADG731_LIB_VERSION: %s\n", (char *) ADG731_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  ADG731 ADG(10, 11, 12);

  assertEqual(32, ADG.channelCount());
  assertEqual(ADG731_ALLOFF, ADG.getChannel());
}


unittest(test_constants)
{
  assertEqual(0x80, ADG731_ALLOFF);
}


unittest(test_allOff)
{
  ADG731 ADG(10, 11, 12);
  //  test default
  assertEqual(ADG731_ALLOFF, ADG.getChannel());

  ADG.setChannel(13);
  ADG.allOff();
  assertEqual(ADG731_ALLOFF, ADG.getChannel());
}


unittest(test_channel)
{
  ADG731 ADG(10, 11, 12);

  //  0..31
  for (int ch = 0; ch < 32; ch ++)
  {
    ADG.setChannel(ch);
    assertEqual(ch, ADG.getChannel());
  }
}


unittest_main()


//  -- END OF FILE --

