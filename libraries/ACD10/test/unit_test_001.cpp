//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-09-25
// PURPOSE: unit tests for the ACD10 library
//     URL: https://github.com/RobTillaart/ACD10
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
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
// assertNotNull(actual)

#include <ArduinoUnitTests.h>


#include "Arduino.h"
#include "ACD10.h"


unittest_setup()
{
  fprintf(stderr, "ACD10_LIB_VERSION: %s\n", (char *) ACD10_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(ACD10_DEFAULT_ADDRESS, 0x2A);
}


unittest(test_constructor)
{
  ACD10 acd;

  assertEqual(acd.getAddress(), ACD10_DEFAULT_ADDRESS);
  assertEqual(acd.getRequestTime(), 80);
  assertEqual(acd.getLastError(), 0);
  assertEqual(acd.lastRead(), 0);
  assertEqual(acd.getCO2Concentration(), 0);
  assertEqual(acd.getTemperature(), 0);
}


unittest_main()


//  -- END OF FILE --

