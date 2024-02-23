//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-02-23
// PURPOSE: unit tests for the 74HC154 library
//     URL: https://github.com/RobTillaart/74HC154
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
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
// assertNotNull(actual)

#include <ArduinoUnitTests.h>


#include "74HC154.h"


unittest_setup()
{
  fprintf(stderr, "LIB_74HC154_VERSION: %s\n", (char *) LIB_74HC154_VERSION);
}


unittest_teardown()
{
}


unittest(test_setLine)
{
  DEV_74HC154 dev(5, 6, 7, 8);

  for (int i = 0; i < 16; i++)
  {
    assertTrue(dev.setLine(i));
    assertEqual(i, dev.getLine());
  }
  assertFalse(dev.setLine(16));
}


unittest(test_nextLine)
{
  DEV_74HC154 dev(5, 6, 7, 8);

  assertTrue(dev.setLine(0));
  for (int i = 0; i < 16; i++)
  {
    assertEqual(i, dev.getLine());
    dev.nextLine();
  }
}


unittest(test_prevLine)
{
  DEV_74HC154 dev(5, 6, 7, 8);

  assertTrue(dev.setLine(15));
  for (int i = 15; i > 0; i--)
  {
    assertEqual(i, dev.getLine());
    dev.prevLine();
  }
}


unittest_main()


//  -- END OF FILE --

