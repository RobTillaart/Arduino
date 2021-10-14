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

#define A0      0


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_add)
{
  fprintf(stderr, "MINMAX_LIB_VERSION: %s\n", (char *) MINMAX_LIB_VERSION);

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
  fprintf(stderr, "MINMAX_LIB_VERSION: %s\n", (char *) MINMAX_LIB_VERSION);

  MINMAX mm;
  
  for (int i = 0; i < 10; i++)
  {
    mm.add(i);
  }
  mm.reset();
  assertEqual(0, mm.minimum());
  assertEqual(0, mm.maximum());
  assertEqual(0, mm.count());
}


unittest(test_autoReset)
{
  fprintf(stderr, "MINMAX_LIB_VERSION: %s\n", (char *) MINMAX_LIB_VERSION);

  MINMAX mm;

  mm.autoReset(10);
  
  for (int i = 0; i < 15; i++)
  {
    mm.add(i);
  }
  assertEqual(10, mm.minimum());
  assertEqual(14, mm.maximum());
  assertEqual(5, mm.count());
}




unittest_main()


// -- END OF FILE --
