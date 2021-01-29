//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-14
// PURPOSE: unit tests for the BoolArray library
//          https://github.com/RobTillaart/BoolArray
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
#include "BoolArray.h"


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  BoolArray ba;
  assertEqual(0, ba.size());
  ba.begin(1000);
  assertEqual(1000, ba.size());

  fprintf(stderr, "\tVERSION:\t %s\n", BOOLARRAY_LIB_VERSION);
}


unittest(test_set_get_toggle)
{
  BoolArray ba;

  ba.begin(1000);
  assertEqual(1000, ba.size());

  fprintf(stderr, "\t1000x set(i, 0) -> sum += get(i)\n");
  int sum = 0;
  for (int i = 0; i < 1000; i++)
  {
    ba.set(i, 0);
  }
  for (int i = 0; i < 1000; i++)
  {
    sum += ba.get(i);
  }
  assertEqual(0, sum);

  fprintf(stderr, "\t1000x set(i, 1) -> sum += get(i)\n");
  sum = 0;
  for (int i = 0; i < 1000; i++)
  {
    ba.set(i, 1);
  }
  for (int i = 0; i < 1000; i++)
  {
    sum += ba.get(i);
  }
  assertEqual(1000, sum);
  
  fprintf(stderr, "\t1000x toggle(i)\n");
  sum = 0;
  for (int i = 0; i < 1000; i++)
  {
    ba.toggle(i);
  }
  for (int i = 0; i < 1000; i++)
  {
    sum += ba.get(i);
  }
  assertEqual(0, sum);
}


unittest(test_clear)
{
  BoolArray ba;

  ba.begin(1000);
  assertEqual(1000, ba.size());


  fprintf(stderr, "\t1000x setAll(1) -> clear() -> sum += get(i)\n");
  int sum = 0;
  ba.setAll(1);
  for (int i = 0; i < 1000; i++)
  {
    sum += ba.get(i);
  }
  assertEqual(1000, sum);

  ba.clear();
  sum = 0;
  for (int i = 0; i < 1000; i++)
  {
    sum += ba.get(i);
  }
  assertEqual(0, sum);
}


unittest_main()

// --------
