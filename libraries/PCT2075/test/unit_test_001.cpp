//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-11
// PURPOSE: unit tests for the PCT2075 temperature sensor
//          https://github.com/RobTillaart/PCT2075
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
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

#include <ArduinoUnitTests.h>


#include "Arduino.h"
#include "PCT2075.h"

// writing to a virtual device does not work
// as millis() function is not implemented in 
// the Arduino-CI environment


unittest_setup()
{
  fprintf(stderr, "PCT2075_LIB_VERSION: %s\n", (char *) PCT2075_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0x00, PCT2075_OK);
  assertEqual(0x82, PCT2075_I2C_ERROR);
}


unittest(test_constructor)
{
  PCT2075 pct(0x30);

  Wire.begin();

  //  TODO
  assertEqual(0, 0);
}


unittest_main()


//  -- END OF FILE --
