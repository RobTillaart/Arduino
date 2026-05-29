//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-xx-xx
// PURPOSE: unit tests for the I2C_ABP2 library
//     URL: https://github.com/RobTillaart/I2C_ABP2
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
#include "I2C_ABP2.h"


unittest_setup()
{
  fprintf(stderr, "I2C_ABP2_LIB_VERSION: %s\n", (char *) I2C_ABP2_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(   0, I2C_ABP2_OK           );
  assertEqual(-100, I2C_ABP2_NOT_READY    );
  assertEqual(-101, I2C_ABP2_REQUEST_ERROR);
}


unittest(test_constructor)
{
  I2C_ABP2 sensor(0x28);
  assertEqual(0x28, sensor.getAddress());

  assertEqual(   0, sensor.lastRead());
}


unittest_main()


//  -- END OF FILE --

