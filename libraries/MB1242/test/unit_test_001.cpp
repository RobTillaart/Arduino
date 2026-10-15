//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-10-13
// PURPOSE: unit tests for the MB1242 library
//     URL: https://github.com/RobTillaart/MB1242
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


#include "MB1242.h"


unittest_setup()
{
  fprintf(stderr, "MB1242_LIB_VERSION: %s\n", (char *) MB1242_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(1, 1);
}

unittest(test_error_codes)
{
  assertEqual(00, MB1242_OK);
  assertEqual(16, MB1242_NOT_READY);
  assertEqual(17, MB1242_REQUEST_ERROR);
  assertEqual(18, MB1242_NO_REQUEST_PENDING);
  assertEqual(19, MB1242_INVALID_ADDRESS);
}


unittest(test_constructor)
{
  MB1242 MB(0x70);
  //  some defaults
  assertEqual(MB1242_OK, MB.getLastError());
  assertEqual(0, MB.lastRead());
  assertEqual(0, MB.lastRequest());
  assertFalse(MB.requestInProgress());
}


unittest_main()


//  -- END OF FILE --

