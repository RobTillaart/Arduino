//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-04-29
// PURPOSE: unit tests for the US500 library
//     URL: https://github.com/RobTillaart/US500
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
#include "US500.h"


unittest_setup()
{
  fprintf(stderr, "US500_LIB_VERSION: %s\n", (char *) US500_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(-1, US500_CMD_ERROR);
  assertEqual(-2, US500_CRC_ERROR);
  assertEqual(-3, US500_TIMEOUT_ERROR);
}


// unittest(test_constructor)
// {
  // US500 obj;
// }


unittest_main()


//  -- END OF FILE --

