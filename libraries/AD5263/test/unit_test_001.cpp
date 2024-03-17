//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-01-09
// PURPOSE: unit tests for  I2C digital potentiometer AD5263 and compatibles.
//          https://github.com/RobTillaart/AD5263
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

#include "AD5263.h"


unittest_setup()
{
  fprintf(stderr, "\nAD5263_LIB_VERSION: %s\n", (char *) AD5263_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0,   AD5263_OK);
  assertEqual(100, AD5263_ERROR);
  assertEqual(128, AD5263_MIDPOINT);
}


unittest(test_constructors)
{
  Wire.begin();

  AD5263 ADx(0x2C);  //  AD0 & AD1 == GND
  assertEqual(128, ADx.read(0));
  assertEqual(128, ADx.read(1));
  assertEqual(128, ADx.read(2));
  assertEqual(128, ADx.read(3));
}


unittest(test_reset)
{
  AD5263 ADx(0x2C);  //  AD0 & AD1 == GND
  Wire.begin();

  assertEqual(128, ADx.read(0));
  assertEqual(128, ADx.read(1));
  assertEqual(128, ADx.read(2));
  assertEqual(128, ADx.read(3));

  ADx.zeroAll();
  assertEqual(0, ADx.read(0));
  assertEqual(0, ADx.read(1));
  assertEqual(0, ADx.read(2));
  assertEqual(0, ADx.read(3));

  ADx.reset();
  assertEqual(128, ADx.read(0));
  assertEqual(128, ADx.read(1));
  assertEqual(128, ADx.read(2));
  assertEqual(128, ADx.read(3));

  ADx.zeroAll();
  assertEqual(0, ADx.read(0));
  assertEqual(0, ADx.read(1));
  assertEqual(0, ADx.read(2));
  assertEqual(0, ADx.read(3));

  ADx.midScaleReset(0);
  assertEqual(128, ADx.read(0));
  ADx.midScaleReset(1);
  assertEqual(128, ADx.read(1));
  ADx.midScaleReset(0);
  assertEqual(128, ADx.read(0));
  ADx.midScaleReset(1);
  assertEqual(128, ADx.read(1));
}


unittest(test_write_read)
{
  AD5263 ADx(0x2C);  //  AD0 & AD1 == GND
  Wire.begin();

  assertEqual(128, ADx.read(0));
  assertEqual(128, ADx.read(1));
  assertEqual(128, ADx.read(2));
  assertEqual(128, ADx.read(3));

  ADx.write(0, 42);
  assertEqual(42, ADx.read(0));
  assertEqual(128, ADx.read(1));
  assertEqual(128, ADx.read(2));
  assertEqual(128, ADx.read(3));

  ADx.write(1, 42);
  assertEqual(42, ADx.read(0));
  assertEqual(42, ADx.read(1));
  assertEqual(128, ADx.read(2));
  assertEqual(128, ADx.read(3));
}


unittest(test_O1_O2)
{
  AD5263 ADx(0x2C);  //  AD0 & AD1 == GND
  Wire.begin();

  assertEqual(0, ADx.getO1());
  assertEqual(0, ADx.getO2());

  ADx.setO1();
  assertEqual(1, ADx.getO1());
  assertEqual(0, ADx.getO2());

  ADx.setO2();
  assertEqual(1, ADx.getO1());
  assertEqual(1, ADx.getO2());

  ADx.setO1(0);
  assertEqual(0, ADx.getO1());
  assertEqual(1, ADx.getO2());

  ADx.setO2(0);
  assertEqual(0, ADx.getO1());
  assertEqual(0, ADx.getO2());

  ADx.write(0, 0, 1, 1);
  assertEqual(1, ADx.getO1());
  assertEqual(1, ADx.getO2());
}


unittest_main()


//  -- END OF FILE --
