//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-08-10
// PURPOSE: unit tests for the DS3502 library
//     URL: https://github.com/RobTillaart/DS3502
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


#include "DS3502.h"


unittest_setup()
{
  fprintf(stderr, "DS3502_LIB_VERSION: %s\n", (char *) DS3502_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  fprintf(stderr, "Error codes");
  assertEqual(DS3502_OK           , 0x00);
  assertEqual(DS3502_READ_ERROR   , 0x01);
  assertEqual(DS3502_REQUEST_ERROR, 0x02);
  assertEqual(DS3502_CONNECT_ERROR, 0x03);
  assertEqual(DS3502_VALUE_ERROR  , 0x04);

  fprintf(stderr, "\nOther");
  assertEqual(DS3502_MIDDLE_VALUE, 0x40);
  assertEqual(DS3502_MAX_OHM, 10000);
}


unittest(test_constructor)
{
  DS3502 ds(0x28);
  assertEqual(0x28, ds.getAddress());
}


unittest_main()


//  -- END OF FILE --

