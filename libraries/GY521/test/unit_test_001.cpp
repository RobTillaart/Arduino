//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-24
// PURPOSE: unit tests for the GY521
//          https://github.com/RobTillaart/GY521
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
#include "GY521.h"



unittest_setup()
{
}

unittest_teardown()
{
}

/*
unittest(test_new_operator)
{
  assertEqualINF(exp(800));
  assertEqualINF(0.0/0.0);
  assertEqualINF(42);
  
  assertEqualNAN(INFINITY - INFINITY);
  assertEqualNAN(0.0/0.0);
  assertEqualNAN(42);
}
*/

unittest(test_constructor)
{
  GY521 sensor(0x69);
  fprintf(stderr, "VERSION: %s\n", GY521_LIB_VERSION);
  sensor.begin();
  assertEqual(GY521_OK, sensor.getError());

  assertTrue(sensor.isConnected());
}


unittest(test_get_set)
{
  GY521 sensor(0x69);
  fprintf(stderr, "VERSION: %s\n", GY521_LIB_VERSION);
  sensor.begin();
  assertEqual(GY521_OK, sensor.getError());
  
  sensor.setThrottle(true);
  assertTrue(sensor.getThrottle());
  sensor.setThrottle(false);
  assertFalse(sensor.getThrottle());
  
  fprintf(stderr, "setThrottleTime()\n");
  for (uint16_t ti = 1; ti != 0; ti <<= 1)
  {
    sensor.setThrottleTime(ti);
    fprintf(stderr, "%d\t", sensor.getThrottleTime());
    assertEqual(ti, sensor.getThrottleTime());
  }

  fprintf(stderr, "setAccelSensitivity() - fails \n");
  for (int as = 0; as < 4; as++)
  {
    sensor.setAccelSensitivity(as);
    // fprintf(stderr, "%d\n", sensor.getAccelSensitivity());
    assertEqual(255, sensor.getAccelSensitivity());
  }

  fprintf(stderr, "setGyroSensitivity() - fails \n");
  for (int gs = 0; gs < 4; gs++)
  {
    sensor.setGyroSensitivity(gs);
    // fprintf(stderr, "%d\n", sensor.getAccelSensitivity());
    assertEqual(255, sensor.getAccelSensitivity());
  }

}

unittest_main()

// --------
