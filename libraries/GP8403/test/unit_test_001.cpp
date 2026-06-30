//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-01-30
// PURPOSE: unit tests for the GP8403 library
//     URL: https://github.com/RobTillaart/GP8403
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
#include "GP8403.h"


unittest_setup()
{
  fprintf(stderr, "GP8403_LIB_VERSION: %s\n", (char *) GP8403_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0x38, GP8403_DEFAULT_ADDRESS);
  assertEqual(0x00, GP8403_OK);
}



unittest_main()


//  -- END OF FILE --

