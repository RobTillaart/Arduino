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
  fprintf(stderr, "GY521_LIB_VERSION: %s\n", (char *) GY521_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  GY521 sensor(0x69);

  Wire.begin();
  sensor.begin();
  assertEqual(GY521_OK, sensor.getError());

  assertTrue(sensor.isConnected());  // incorrect but OK
}


unittest(test_get_set_throttle)
{
  GY521 sensor(0x69);

  Wire.begin();
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
}



unittest(test_get_set_sensitivity)
{
  GY521 sensor(0x69);

  Wire.begin();
  sensor.begin();

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


unittest(test_constants)
{
  assertEqual(GY521_OK,                   0);
  assertEqual(GY521_THROTTLED,            1);
  assertEqual(GY521_ERROR_READ,           -1);
  assertEqual(GY521_ERROR_WRITE,          -2);
  assertEqual(GY521_ERROR_NOT_CONNECTED,  -3);

  assertEqual(GY521_THROTTLE_TIME,        10);

  assertEqualFloat(GY521_RAD2DEGREES, 180.0 / PI,    0.001);
  assertEqualFloat(GY521_RAW2DPS,     1.0 / 131.0,   0.001);
  assertEqualFloat(GY521_RAW2G,       1.0 / 16384.0, 0.000001);
}


unittest(test_initial_values)
{
  GY521 sensor(0x69);

  Wire.begin();

  assertEqualFloat(0, sensor.getAccelX(), 0.0001);
  assertEqualFloat(0, sensor.getAccelY(), 0.0001);
  assertEqualFloat(0, sensor.getAccelZ(), 0.0001);

  assertEqualFloat(0, sensor.getAngleX(), 0.0001);
  assertEqualFloat(0, sensor.getAngleY(), 0.0001);
  assertEqualFloat(0, sensor.getAngleZ(), 0.0001);

  assertEqualFloat(0, sensor.getGyroX(), 0.0001);
  assertEqualFloat(0, sensor.getGyroY(), 0.0001);
  assertEqualFloat(0, sensor.getGyroZ(), 0.0001);
  
  assertEqualFloat(0, sensor.getPitch(), 0.0001);
  assertEqualFloat(0, sensor.getRoll(),  0.0001);
  assertEqualFloat(0, sensor.getYaw(),   0.0001);

  fprintf(stderr, "\nother values()\n");
  assertEqualFloat(0, sensor.getTemperature(), 0.0001);
  assertEqual(0, sensor.lastTime() );
  assertEqual(0, sensor.getError() );
}


unittest(test_initial_calibration_errors)
{
  GY521 sensor(0x69);

  Wire.begin();

  assertEqualFloat(0, sensor.axe, 0.0001);
  assertEqualFloat(0, sensor.aye, 0.0001);
  assertEqualFloat(0, sensor.aze, 0.0001);

  assertEqualFloat(0, sensor.gxe, 0.0001);
  assertEqualFloat(0, sensor.gye, 0.0001);
  assertEqualFloat(0, sensor.gze, 0.0001);
}


unittest_main()


//  -- END OF FILE --

