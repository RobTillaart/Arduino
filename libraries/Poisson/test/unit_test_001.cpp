//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-05-29
// PURPOSE: unit tests for the Poisson library
//          https://github.com/RobTillaart/Poisson
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
#include "Poisson.h"


unittest_setup()
{
    fprintf(stderr, "POISSON_LIB_VERSION: %s\n", (char *) POISSON_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  Poisson P;

  assertEqual(1, 1);
}


unittest_main()


//  -- END OF FILE --

