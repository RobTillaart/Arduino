//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-01-17
// PURPOSE: unit tests for the millis64 library
//     URL: https://github.com/RobTillaart/millis64
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
#include "millis64.h"


unittest_setup()
{
  fprintf(stderr, "MILLIS64_LIB_VERSION: %s\n", (char *) MILLIS64_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_none)
{
  assertEqual(0, 0);
}


unittest_main()


//  -- END OF FILE --

