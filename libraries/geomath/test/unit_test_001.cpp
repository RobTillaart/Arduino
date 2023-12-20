//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-09-24
// PURPOSE: unit tests for the geomath library
//          https://github.com/RobTillaart/geomath
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
#include "geomath.h"

#define A0      0


unittest_setup()
{
    fprintf(stderr, "GEOMATH_LIB_VERSION: %s\n", (char *) GEOMATH_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqualFloat(1, 1,    0.001);
}


unittest_main()


//  -- END OF FILE --
