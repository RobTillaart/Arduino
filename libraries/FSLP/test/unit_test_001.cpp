//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-04-18
// PURPOSE: unit tests for the FSLP library
//     URL: https://github.com/RobTillaart/FSLP
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
#include "FSLP.h"


unittest_setup()
{
  fprintf(stderr, "FSLP_LIB_VERSION: %s\n", (char *) FSLP_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqualFloat  (FSLP_NO_PRESSURE, 0.0, 0.001);
}


unittest(test_constructor)
{
  FSLP obj(14, 4,15,5);
}


unittest_main()


//  -- END OF FILE --

