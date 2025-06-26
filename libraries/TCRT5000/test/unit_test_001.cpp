//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-06-20
// PURPOSE: unit tests for the TCRT5000 library
//     URL: https://github.com/RobTillaart/TCRT5000
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
#include "TCRT5000.h"


unittest_setup()
{
  fprintf(stderr, "TCRT5000_LIB_VERSION: %s\n", (char *) TCRT5000_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(500, TCRT5000_DEFAULT_THRESHOLD);
}


unittest(test_constructor)
{
  TCRT5000 sensor(14);
  
  assertEqual(0, sensor.lastRead());
}


unittest(test_threshold)
{
  TCRT5000 sensor(14);

  for (int t = 100; t <= 1000; t += 100)
  {
    sensor.setThreshold(t);
    assertEqual(t, sensor.getThreshold());
  }
}


unittest_main()


//  -- END OF FILE --

