//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-01
// PURPOSE: unit tests for the MS5611 temperature and pressure library
//          https://github.com/RobTillaart/MS5611
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual);               // a == b
// assertNotEqual(unwanted, actual);            // a != b
// assertComparativeEquivalent(expected, actual);    // abs(a - b) == 0 or (!(a > b) && !(a < b))
// assertComparativeNotEquivalent(unwanted, actual); // abs(a - b) > 0  or ((a > b) || (a < b))
// assertLess(upperBound, actual);              // a < b
// assertMore(lowerBound, actual);              // a > b
// assertLessOrEqual(upperBound, actual);       // a <= b
// assertMoreOrEqual(lowerBound, actual);       // a >= b
// assertTrue(actual);
// assertFalse(actual);
// assertNull(actual);

// // special cases for floats
// assertEqualFloat(expected, actual, epsilon);    // fabs(a - b) <= epsilon
// assertNotEqualFloat(unwanted, actual, epsilon); // fabs(a - b) >= epsilon
// assertInfinity(actual);                         // isinf(a)
// assertNotInfinity(actual);                      // !isinf(a)
// assertNAN(arg);                                 // isnan(a)
// assertNotNAN(arg);                              // !isnan(a)


#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "MS5611.h"


unittest_setup()
{
  fprintf(stderr, "MS5611_LIB_VERSION: %s\n", (char *) MS5611_LIB_VERSION );
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


unittest(test_constants)
{
  assertEqual(MS5611_READ_OK , 0);
  assertEqual(MS5611_ERROR_2 , 2); 
  assertEqual(MS5611_NOT_READ, -999);
}



unittest(test_constructor)
{
  MS5611 sensor(0x77);

  Wire.begin();
  assertFalse(sensor.begin());  // as there is no sensor, and no ROM values.

  assertEqualFloat(-9.99, sensor.getTemperature(), 0.01);
  assertEqualFloat(-9.99, sensor.getPressure(),    0.01);
  assertEqual(0, sensor.getLastResult());
  assertEqual(0, sensor.lastRead());
}


unittest(test_read_sensor)
{
  MS5611 sensor(0x77);

  Wire.begin();
  assertFalse(sensor.begin());

  assureEqual(MS5611_READ_OK, sensor.read());

  // as Wire not implemented in tests
  // assertEqual(MS5611_NOT_READ, sensor.getTemperature());
  // assertEqual(MS5611_NOT_READ, sensor.getPressure());
  // assertEqual(MS5611_NOT_READ, sensor.getLastResult());
  // assertEqual(0, sensor.lastRead());
}


unittest(test_overSampling)
{
  MS5611 sensor(0x77);

  Wire.begin();
  assertFalse(sensor.begin());

  // default
  assureEqual(OSR_ULTRA_LOW, sensor.getOversampling());

  sensor.setOversampling(OSR_ULTRA_LOW);
  assureEqual(OSR_ULTRA_LOW, sensor.getOversampling());
  sensor.setOversampling(OSR_LOW);
  assureEqual(OSR_LOW, sensor.getOversampling());
  sensor.setOversampling(OSR_STANDARD);
  assureEqual(OSR_STANDARD, sensor.getOversampling());
  sensor.setOversampling(OSR_HIGH);
  assureEqual(OSR_HIGH, sensor.getOversampling());
  sensor.setOversampling(OSR_ULTRA_HIGH);
  assureEqual(OSR_ULTRA_HIGH, sensor.getOversampling());
}


unittest_main()


//  -- END OF FILE --

