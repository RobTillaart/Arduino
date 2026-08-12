//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-08-12
// PURPOSE: unit tests for the DS3501 library
//     URL: https://github.com/RobTillaart/DS3501
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


#include "DS3501.h"


unittest_setup()
{
  fprintf(stderr, "DS3501_LIB_VERSION: %s\n", (char *) DS3501_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  fprintf(stderr, "Error codes");
  assertEqual(DS3501_OK,             0x00);
  assertEqual(DS3501_READ_ERROR,     0x01);
  assertEqual(DS3501_REQUEST_ERROR,  0x02);
  assertEqual(DS3501_CONNECT_ERROR,  0x03);
  assertEqual(DS3501_VALUE_ERROR,    0x04);
  assertEqual(DS3501_LUTINDEX_ERROR, 0x05);

  fprintf(stderr, "\nModi");
  assertEqual(DS3501_DEFAULT_MODE, 0x00);
  assertEqual(DS3501_LUT_MODE, 0x01);
  assertEqual(DS3501_LUT_ADDER_MODE, 0x03);

  fprintf(stderr, "\nOther");
  assertEqual(DS3501_MIDDLE_VALUE, 0x40);
  assertEqual(DS3501_MAX_OHM, 10000);
}


unittest(test_constructor)
{
  DS3501 ds(0x28);
  assertEqual(0x28, ds.getAddress());
}


unittest_main()


//  -- END OF FILE --

