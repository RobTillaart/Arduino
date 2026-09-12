//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-09-11
// PURPOSE: unit tests for the DS1682 library
//     URL: https://github.com/RobTillaart/DS1682
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


#include "DS1682.h"


unittest_setup()
{
  fprintf(stderr, "DS1682_LIB_VERSION: %s\n", (char *) DS1682_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(1, 1);
}


unittest(test_constructor)
{
  DS1682 upTimer;  //  fixed address
  
  //  Wire.begin();
  //  upTimer.begin();

  assertEqual(0x6A, upTimer.getAddress());
}


unittest_main()


//  -- END OF FILE --

