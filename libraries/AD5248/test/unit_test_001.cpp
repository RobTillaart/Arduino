//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-12-12
// PURPOSE: unit tests for I2C digital PotentioMeter AD5243 + rheostat AD5248
//          https://github.com/RobTillaart/AD5243_RT
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

#include "AD5248.h"


unittest_setup()
{
  fprintf(stderr, "\nAD5248_LIB_VERSION: %s\n", (char *) AD5248_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructors)
{
  Wire.begin();

  AD5243 ADx;
  assertEqual(0x2F, ADx.getAddress());
  assertEqual(127, ADx.read(0));
  assertEqual(127, ADx.read(1));

  AD5248 AD1(0x2C);
  assertEqual(0x2C, AD1.getAddress());
  assertEqual(127, AD1.read(0));
  assertEqual(127, AD1.read(1));
}


unittest(test_pmCount)
{
  Wire.begin();

  AD5243 ADx;
  assertEqual(2, ADx.pmCount());

  AD5248 AD1(0x2C);
  assertEqual(2, ADx.pmCount());
}


unittest(test_reset)
{
  AD5243 AD;
  Wire.begin();

  assertEqual(127, AD.read(0));
  assertEqual(127, AD.read(1));

  AD.zeroAll();
  assertEqual(0, AD.read(0));
  assertEqual(0, AD.read(1));

  AD.reset();
  assertEqual(127, AD.read(0));
  assertEqual(127, AD.read(1));

  AD.zeroAll();
  assertEqual(0, AD.read(0));
  assertEqual(0, AD.read(1));

  AD.midScaleReset(0);
  assertEqual(127, AD.read(0));
  assertEqual(0, AD.read(1));
  AD.midScaleReset(1);
  assertEqual(127, AD.read(0));
  assertEqual(127, AD.read(1));
}


unittest(test_write_read)
{
  AD5243 AD;
  Wire.begin();

  assertEqual(127, AD.read(0));
  assertEqual(127, AD.read(1));

  AD.write(0, 42);
  assertEqual(42, AD.read(0));
  assertEqual(127, AD.read(1));

  AD.write(1, 42);
  assertEqual(42, AD.read(0));
  assertEqual(42, AD.read(1));
}


unittest(test_constants)
{
  assertEqual(0, AD5248_OK);
  assertEqual(100, AD5248_ERROR);
  assertEqual(127, AD5248_MIDPOINT);
}


unittest_main()


//  -- END OF FILE --
