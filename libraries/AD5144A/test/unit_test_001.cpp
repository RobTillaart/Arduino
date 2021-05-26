//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
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
}


unittest_teardown()
{
}


unittest(test_constructors)
{
  Wire.begin();

  AD5144A ADx(0x2C);
  assertEqual(1, 1);
}


unittest_main()

// --------
