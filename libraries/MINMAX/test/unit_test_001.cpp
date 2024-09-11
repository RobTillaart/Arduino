//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-10-14
// PURPOSE: unit tests for the MINMAX library
//          https://github.com/RobTillaart/MINMAX
//
// https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
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
#include "MINMAX.h"


unittest_setup()
{
  fprintf(stderr, "MINMAX_LIB_VERSION: %s\n", (char *) MINMAX_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(MINMAX_NO_CHANGE  , 0X00);
  assertEqual(MINMAX_MIN_CHANGED, 0X01);
  assertEqual(MINMAX_MAX_CHANGED, 0X02);
  assertEqual(MINMAX_RESET_DONE , 0X80);
}


unittest(test_add)
{
  MINMAX mm;

  for (int i = 0; i < 1000; i++)
  {
    mm.add(i);
  }
  assertEqual(0, mm.minimum());
  assertEqual(999, mm.maximum());
  assertEqual(1000, mm.count());
}


unittest(test_reset)
{
  MINMAX mm;

  for (int i = 0; i < 10; i++)
  {
    mm.add(i);
  }
  assertEqual(0, mm.minimum());
  assertEqual(9, mm.maximum());
  assertEqual(10, mm.count());
  mm.reset();
  assertEqual(0, mm.minimum());
  assertEqual(0, mm.maximum());
  assertEqual(0, mm.count());
}


unittest(test_autoReset)
{
  MINMAX mm;

  mm.setAutoResetCount(10);

  for (int i = 0; i < 15; i++)
  {
    mm.add(i);
  }
  assertEqual(10, mm.minimum());
  assertEqual(14, mm.maximum());
  assertEqual(5, mm.count());

  assertEqual(10, mm.getAutoResetCount());
}


unittest(test_lastValue)
{
  MINMAX mm;

  for (int i = 0; i < 10; i++)
  {
    mm.add(i);
  }
  assertEqual(9, mm.lastValue());
}


unittest(test_dampening)
{
  MINMAX mm;

  for (int i = 0; i < 10; i++)
  {
    mm.setDampening(i);
    assertEqualFloat(i, mm.getDampening(), 0.01);
  }
}


unittest_main()


//  -- END OF FILE --
