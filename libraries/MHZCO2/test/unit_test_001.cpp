//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-12-01
// PURPOSE: Arduino Library for MHZ series CO2 sensors
//          https://github.com/RobTillaart/MHZCO2
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

#include "Arduino.h"
#include "MHZCO2.h"


unittest_setup()
{
    fprintf(stderr, "MHZCO2_LIB_VERSION: %s\n", (char *) MHZCO2_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(   0, MHZCO2_OK);
  assertEqual( -10, MHZCO2_TIMEOUT);
  assertEqual( -11, MHZCO2_ERROR_CRC);
}


unittest(test_constructor)
{
  MHZCO2 A;
  MHZ19B B;

  assertEqual(   0, A.uptime());
  assertEqual(   0, B.uptime());
}


unittest_main()


//  -- END OF FILE --

