//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-09-08
// PURPOSE: unit tests for the L9110 library
//     URL: https://github.com/RobTillaart/L9110
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
#include "L9110.h"


unittest_setup()
{
  fprintf(stderr, "L9110_LIB_VERSION: %s\n", (char *) L9110_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(L9110_STOP   , 0x00);
  assertEqual(L9110_REVERSE, 0x01);
  assertEqual(L9110_FORWARD, 0x02);
}


unittest(test_constructor)
{
  L9110 obj(6, 7);
  
  obj.begin();
  assertEqual(L9110_STOP   , obj.status());
}


unittest_main()


//  -- END OF FILE --

