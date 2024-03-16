//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for I2C digital PotentioMeter AD5241 AD5242
//          https://github.com/RobTillaart/AD524X
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

#include "AD524X.h"


unittest_setup()
{
  fprintf(stderr, "\nAD524X_LIB_VERSION: %s\n", (char *) AD524X_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructors)
{
  Wire.begin();

  AD524X ADx(0x2C);  //  AD0 & AD1 == GND
  assertEqual(127, ADx.read(0));
  assertEqual(127, ADx.read(1));

  AD5241 AD1(0x2C);
  assertEqual(127, AD1.read(0));
  assertEqual(127, AD1.read(1));

  AD5242 AD2(0x2C);
  assertEqual(127, AD2.read(0));
  assertEqual(127, AD2.read(1));

  AD5280 AD3(0x2C);
  assertEqual(127, AD1.read(0));
  assertEqual(127, AD1.read(1));

  AD5282 AD4(0x2C);
  assertEqual(127, AD2.read(0));
  assertEqual(127, AD2.read(1));
}


unittest(test_pmCount)
{
  Wire.begin();

  AD524X ADx(0x2C);  //  AD0 & AD1 == GND
  assertEqual(2, ADx.pmCount());

  AD5241 AD1(0x2C);
  assertEqual(2, ADx.pmCount());

  AD5242 AD2(0x2C);
  assertEqual(2, ADx.pmCount());

  AD5280 AD3(0x2C);
  assertEqual(2, ADx.pmCount());

  AD5282 AD4(0x2C);
  assertEqual(2, ADx.pmCount());
}


unittest(test_reset)
{
  AD524X AD(0x2C);  //  AD0 & AD1 == GND
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
  AD.midScaleReset(1);
  assertEqual(127, AD.read(1));
}


unittest(test_write_read)
{
  AD524X AD(0x2C);  //  AD0 & AD1 == GND
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


unittest(test_O1_O2)
{
  AD524X AD(0x2C);  //  AD0 & AD1 == GND
  Wire.begin();

  assertEqual(0, AD.getO1());
  assertEqual(0, AD.getO2());

  AD.setO1();
  assertEqual(1, AD.getO1());
  assertEqual(0, AD.getO2());

  AD.setO2();
  assertEqual(1, AD.getO1());
  assertEqual(1, AD.getO2());

  AD.setO1(0);
  assertEqual(0, AD.getO1());
  assertEqual(1, AD.getO2());

  AD.setO2(0);
  assertEqual(0, AD.getO1());
  assertEqual(0, AD.getO2());

  AD.write(0, 0, 1, 1);
  assertEqual(1, AD.getO1());
  assertEqual(1, AD.getO2());
}


unittest(test_constants)
{
  assertEqual(0, AD524X_OK);
  assertEqual(100, AD524X_ERROR);
  assertEqual(127, AD524X_MIDPOINT);
}


unittest_main()


//  -- END OF FILE --
