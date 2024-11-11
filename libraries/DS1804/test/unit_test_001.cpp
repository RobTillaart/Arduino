//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-11-11
// PURPOSE: unit tests for the DS1804 library
//          https://github.com/RobTillaart/DS1804
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
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


#include "DS1804.h"


unittest_setup()
{
  fprintf(stderr, "DS1804_LIB_VERSION: %s\n", (char *) DS1804_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  DS1804 ds(6,7,8);

  assertEqual(1,1);
}

unittest_main()


//  -- END OF FILE --
