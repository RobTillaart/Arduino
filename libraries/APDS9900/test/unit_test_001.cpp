//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-01-05
// PURPOSE: unit tests for the APDS9900 library
//     URL: https://github.com/RobTillaart/APDS9900
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
#include "APDS9900.h"


unittest_setup()
{
  fprintf(stderr, "APDS9900_LIB_VERSION: %s\n", (char *) APDS9900_LIB_VERSION);
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
  APDS9900 apds;

  assertEqual(0x39, apds.getAddress());
}


unittest_main()


//  -- END OF FILE --

