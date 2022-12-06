//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-12-06
// PURPOSE: unit tests for I2C digital MSP300 pressure transducer.
//          https://github.com/RobTillaart/MSP300
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

#include "MSP300.h"


unittest_setup()
{
  fprintf(stderr, "\nMSP300_LIB_VERSION %s\n", (char*) MSP300_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(000, MSP300_OK);
  assertEqual(100, MSP300_ERROR);
}


unittest(test_constructors)
{
  Wire.begin();

  MSP300 MSP(0x2C);
  MSP.begin(100);
  //  assertEqual(0, MSP.read());
  assertEqual(1, 1);
}



unittest_main()

// --------
