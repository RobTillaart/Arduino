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
  assertEqual(001, MSP300_RESERVED);
  assertEqual(002, MSP300_STALE_DATA);
  assertEqual(003, MSP300_READ_ERROR);
  assertEqual(100, MSP300_REQUEST_ERROR);
}


unittest(test_constructor)
{
  Wire.begin();

  MSP300 MSP(0x28);
  MSP.begin(100);
  //  assertEqual(0, MSP.read());
  assertEqual(MSP300_OK, MSP.lastError());

  assertEqual(0, MSP.getStatus());
  assertEqual(0, MSP.getPressure());
  assertEqual(0, MSP.getTemperature());
}


unittest(test_PressureCount)
{
  Wire.begin();

  MSP300 MSP(0x28);

  //  default values
  assertEqual(1000, MSP.getPmin());
  assertEqual(15000, MSP.getPmax());

  //  changed values
  MSP.setPressureCounts(1012, 14980);
  assertEqual(1012, MSP.getPmin());
  assertEqual(14980, MSP.getPmax());
}


unittest_main()


//  -- END OF FILE --

