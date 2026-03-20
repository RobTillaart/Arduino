//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-03-13
// PURPOSE: unit tests for the TRAFO library
//     URL: https://github.com/RobTillaart/TRAFO
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
#include "TRAFO.h"


//  dummy
int32_t readADC()
{
  return 1234;
}


unittest_setup()
{
  fprintf(stderr, "TRAFO_LIB_VERSION: %s\n", (char *) TRAFO_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqualFloat(50.0, TRAFO_DEFAULT_FREQUENCY, 0.01);
}


unittest_main()


//  -- END OF FILE --

