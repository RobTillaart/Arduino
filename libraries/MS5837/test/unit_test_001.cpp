//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-06
// PURPOSE: unit tests for the MS5837 current sensor
//          https://github.com/RobTillaart/MS5837
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
#include "MS5837.h"

#define A0      0


unittest_setup()
{
    fprintf(stderr, "MS5837_LIB_VERSION: %s\n", (char *) MS5837_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(MS5803_TYPE_01,  1);
  assertEqual(MS5837_TYPE_02,  2);
  assertEqual(MS5837_TYPE_30, 30);
}



unittest_main()


//  -- END OF FILE --
