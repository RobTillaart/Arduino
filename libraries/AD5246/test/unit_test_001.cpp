//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-08-02
// PURPOSE: unit tests for I2C digital rheostat AD5246
//          https://github.com/RobTillaart/AD5246
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

#include "AD5246.h"


unittest_setup()
{
  fprintf(stderr, "\nAD5246_LIB_VERSION %s\n", (char*) AD5246_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(000, AD5246_OK);
  assertEqual(100, AD5246_ERROR);
  assertEqual( 64, AD5246_MIDPOINT);
}


unittest(test_constructors)
{
  Wire.begin();

  AD5246 AD;
  AD.begin();
  assertEqual(64, AD.read());
}


unittest(test_reset)
{
  Wire.begin();
  AD5246 AD;

  assertEqual(64, AD.read());

  AD.write(0);
  assertEqual(0, AD.read());

  AD.reset();
  assertEqual(64, AD.read());
}


unittest(test_write_read)
{
  Wire.begin();
  AD5246 AD;

  assertEqual(64, AD.read());

  AD.write(42);
  assertEqual(42, AD.read());
}


unittest_main()


//  -- END OF FILE --
