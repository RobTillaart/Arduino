//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2024-11-27
// PURPOSE: unit tests for the AD5933R IO device
//          https://github.com/RobTillaart/AD5933R
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
#include "AD5593R.h"


unittest_setup()
{
  fprintf(stderr, "AD5593R_LIB_VERSION:\t%s\n", (char *) AD5593R_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0x0000, AD5593R_OK);
  assertEqual(0xFF81, AD5593R_PIN_ERROR);
  assertEqual(0xFF82, AD5593R_I2C_ERROR);
}


unittest(test_getAddress)
{
  AD5593R ad(0x08);

  assertEqual(0x08, ad.getAddress());
}


unittest_main()


//  -- END OF FILE --

