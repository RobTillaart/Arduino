//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-02-02
// PURPOSE: unit tests for the map2bit library
//          https://github.com/RobTillaart/map2bits
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


#include "map2bits.h"


unittest_setup()
{
  fprintf(stderr, "MAP2BITS_LIB_VERSION: %s\n", (char *) MAP2BITS_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  map2bits mb;
  assertTrue(mb.init(0, 100, 10));

  assertEqual(0, mb.map(-10));
  assertEqual(0, mb.map(0));
  assertEqual(0, mb.map(4));
  assertEqual(1, mb.map(5));
  assertEqual(1, mb.map(14));
  assertEqual(3, mb.map(15));
  assertEqual(3, mb.map(24));
  assertEqual(7, mb.map(25));
  assertEqual(7, mb.map(34));
  assertEqual(15, mb.map(35));
  assertEqual(15, mb.map(44));
  assertEqual(31, mb.map(45));
  assertEqual(31, mb.map(54));
  assertEqual(63, mb.map(55));
  assertEqual(63, mb.map(64));
  assertEqual(127, mb.map(65));
  assertEqual(127, mb.map(74));
  assertEqual(255, mb.map(75));
  assertEqual(255, mb.map(84));
  assertEqual(511, mb.map(85));
  assertEqual(511, mb.map(94));
  assertEqual(1023, mb.map(100));
  assertEqual(1023, mb.map(1000));
}


unittest_main()


//  -- END OF FILE --

