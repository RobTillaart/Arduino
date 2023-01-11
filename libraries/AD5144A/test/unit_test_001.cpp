//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-04-30
// PURPOSE: unit tests for I2C digital PotentioMeter AD5144A
//          https://github.com/RobTillaart/AD5144A
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

#include "AD5144A.h"


unittest_setup()
{
  fprintf(stderr, "AD51XXA_VERSION: %s\n", (char *) AD51XXA_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructors)
{
  Wire.begin();

  AD5123 AD23(0x2C);
  assertEqual(  4, AD23.pmCount());
  assertEqual(127, AD23.maxValue());
  // assertEqual(0, AD23.read())     //  todo

  AD5124 AD24(0x2C);
  assertEqual(  4, AD24.pmCount());
  assertEqual(127, AD24.maxValue());

  AD5143 AD43(0x2C);
  assertEqual(  4, AD43.pmCount());
  assertEqual(255, AD43.maxValue());

  AD5144A AD44(0x2C);
  assertEqual(  4, AD44.pmCount());
  assertEqual(255, AD44.maxValue());

  AD5144A AD44A(0x2C);
  assertEqual(  4, AD44A.pmCount());
  assertEqual(255, AD44A.maxValue());

  AD5122A AD22A(0x2C);
  assertEqual(  2, AD22A.pmCount());
  assertEqual(127, AD22A.maxValue());

  AD5142A AD42A(0x2C);
  assertEqual(  2, AD42A.pmCount());
  assertEqual(255, AD42A.maxValue());

  AD5121 AD21(0x2C);
  assertEqual(  1, AD21.pmCount());
  assertEqual(127, AD21.maxValue());

  AD5141 AD41(0x2C);
  assertEqual(  1, AD41.pmCount());
  assertEqual(255, AD41.maxValue());
}


unittest(test_constants)
{
  assertEqual(  0, AD51XXA_OK);
  assertEqual(100, AD51XXA_ERROR);
  assertEqual(101, AD51XXA_INVALID_POT);
  assertEqual(102, AD51XXA_INVALID_VALUE);
}


unittest_main()

// --------
