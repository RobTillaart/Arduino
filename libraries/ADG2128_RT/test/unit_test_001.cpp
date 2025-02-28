//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-28
// PURPOSE: unit tests for the ADG2128 library
//     URL: https://github.com/RobTillaart/ADG2128
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
#include "ADG2128.h"


unittest_setup()
{
  fprintf(stderr, "ADG2128_LIB_VERSION: %s\n", (char *) ADG2128_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(ADG2128_DEFAULT_ADDRESS, 0x70);
  
  assertEqual(ADG2128_OK           , 0x00);
  assertEqual(ADG2128_CRC_ERROR    , 0x01);
  assertEqual(ADG2128_NOT_READY    , 0x10);
  assertEqual(ADG2128_REQUEST_ERROR, 0x11);
}


unittest(test_constructor)
{
  ADG2128 adg;

  assertEqual(adg.getAddress(), ADG2128_DEFAULT_ADDRESS);
  assertEqual(adg.getLastError(), 0);
}


unittest_main()


//  -- END OF FILE --

