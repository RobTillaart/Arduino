//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-09
// PURPOSE: unit tests for the ADT7470 Fan Monitoring library
//          https://github.com/RobTillaart/ADT7470
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

#include "ADT7470.h"


unittest_setup()
{
  fprintf(stderr, "ADT7470_LIB_VERSION: %s\n", (char *)ADT7470_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(1000, ADT7470_TIMEOUT);
  assertEqual(0x2F, ADT7470_ADDR_HIGH);
  assertEqual(0x2C, ADT7470_ADDR_LOW);
  assertEqual(0x2E, ADT7470_ADDR_FLOAT);
}


unittest(test_constructor)
{
  ADT7470 ADT(0x2C);  //  default Wire

  Wire.begin();
  ADT.begin();

  assertFalse(ADT.isConnected());
}


unittest_main()


//  -- END OF FILE -- 

