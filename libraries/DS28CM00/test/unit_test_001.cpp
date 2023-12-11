//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-20
// PURPOSE: unit tests for the DS28CM00
//          https://github.com/RobTillaart/DS28CM00
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

#include "Wire.h"
#include "DS28CM00.h"


unittest_setup()
{
  fprintf(stderr, "DS28CM00_LIB_VERSION: %s\n", (char *) DS28CM00_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0x00, DS28CM00_I2C_MODE    );
  assertEqual(0x01, DS28CM00_SMBUS_MODE  );
  assertEqual(0xFF, DS28CM00_MODE_UNKNOWN);
}


unittest(test_constructor_I)
{
  uint8_t   uid[8];
  DS28CM00  DS28(&Wire);

  Wire.begin();
  DS28.begin();
  uint8_t mode;

  assertFalse(DS28.getMode(mode));           //  not connected...
  assertEqual(DS28CM00_MODE_UNKNOWN, mode);

  assertTrue(DS28.setSMBusMode());           //  apparently 
  assertFalse(DS28.getMode(mode));
  assertEqual(DS28CM00_MODE_UNKNOWN, mode);

  assertTrue(DS28.setI2CMode());
  assertFalse(DS28.getMode(mode));
  assertEqual(DS28CM00_MODE_UNKNOWN, mode);
}


unittest(test_constructor_II)
{
  uint8_t   uid[8];
  DS28CM00  DS28;     // use default Wire

  Wire.begin();
  DS28.begin();
  uint8_t mode;

  assertFalse(DS28.getMode(mode));           //  not connected...
  assertEqual(DS28CM00_MODE_UNKNOWN, mode);
}


unittest_main()


//  -- END OF FILE --

