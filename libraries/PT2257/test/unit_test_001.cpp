//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-01-20
// PURPOSE: unit tests for the PT2257 library
//     URL: https://github.com/RobTillaart/PT2257
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
#include "PT2257.h"


unittest_setup()
{
  fprintf(stderr, "PT2257_LIB_VERSION: %s\n", (char *) PT2257_LIB_VERSION);
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
  PT2257 obj;
}


unittest_main()


//  -- END OF FILE --

