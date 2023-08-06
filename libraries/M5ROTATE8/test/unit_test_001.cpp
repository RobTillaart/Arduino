//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-08-03
// PURPOSE: unit tests for the M5ROTATE8 library
//          https://github.com/RobTillaart/M5ROTATE8
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
#include "m5rotate8.h"


unittest_setup()
{
  fprintf(stderr, "M5ROTATE8_LIB_VERSION: %s\n", (char *) M5ROTATE8_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  M5ROTATE8 MM;

  assertEqual(1, 1);
}


unittest_main()


//  -- END OF FILE --

