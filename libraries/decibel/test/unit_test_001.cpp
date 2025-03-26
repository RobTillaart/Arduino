//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-03-24
// PURPOSE: unit tests for the decibel library
//     URL: https://github.com/RobTillaart/decibel
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


#include "Arduino.h"
#include "decibel.h"


unittest_setup()
{
  fprintf(stderr, "DECIBEL_LIB_VERSION: %s\n", (char *) DECIBEL_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_one)
{
  assertEqual(1, 1);
}


unittest_main()


//  -- END OF FILE --

