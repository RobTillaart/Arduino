//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-28
// PURPOSE: unit tests for the ADG2188 library
//     URL: https://github.com/RobTillaart/ADG2188
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
#include "ADG2188.h"


unittest_setup()
{
  fprintf(stderr, "ADG2188_LIB_VERSION: %s\n", (char *) ADG2188_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(ADG2188_DEFAULT_ADDRESS, 0x70);
  
  assertEqual(ADG2188_OK           , 0x00);
  assertEqual(ADG2188_CRC_ERROR    , 0x80);
  assertEqual(ADG2188_NOT_READY    , 0x81);
  assertEqual(ADG2188_REQUEST_ERROR, 0x82);
  assertEqual(ADG2188_ADDRESS_ERROR, 0x83);
}


unittest(test_constructor)
{
  ADG2188 adg;

  assertEqual(adg.getAddress(), ADG2188_DEFAULT_ADDRESS);
  assertEqual(adg.getLastError(), 0);
}


unittest_main()


//  -- END OF FILE --

