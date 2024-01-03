//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-11-29
// PURPOSE: unit tests for the fast_math library
//          https://github.com/RobTillaart/fast_math
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
#include "fast_math.h"


unittest_setup()
{
  fprintf(stderr, "FASTMATH_LIB_VERSION: %s\n", (char *) FASTMATH_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_I)
{
  assertEqual(1, 1);
}


unittest_main()


//  -- END OF FILE --
