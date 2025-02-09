//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-06
// PURPOSE: unit tests for the OUTPIN library
//          https://github.com/RobTillaart/OUTPIN
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
#include "OUTPIN.h"


unittest_setup()
{
  fprintf(stderr, "OUTPIN_LIB_VERSION: %s\n", (char *) OUTPIN_LIB_VERSION);
}


unittest_teardown()
{
}

unittest(test_constructor)
{
  OUTPIN led(13, LOW);
  assertEqual(1, 1);
}


unittest_main()


//  -- END OF FILE --


