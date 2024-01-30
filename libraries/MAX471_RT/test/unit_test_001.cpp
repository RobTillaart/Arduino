//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-01-30
// PURPOSE: unit tests for the MAX471 current sensor.
//     URL: https://github.com/RobTillaart/MAX471_RT
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

#include "MAX471.h"


unittest_setup()
{
    fprintf(stderr, "MAX471_LIB_VERSION: %s\n", (char *) MAX471_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqualFloat(1, 1, 0.001);
}

//  to elaborate


unittest_main()


//  -- END OF FILE --

