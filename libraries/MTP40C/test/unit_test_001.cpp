//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2021-08-20
// PURPOSE: unit tests for the MTP40C CO2 sensor
//          https://github.com/RobTillaart/MTP40C
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
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



////////////////////////////////////
//
//  MANY TESTS WILL BLOCK AS BUILD CI HAS NO GOOD TIMEOUT
//  ALL FAILING TESTS ARE COMMENTED
//
//  USE GODMODE SERIAL TO IMPROVE THESE TESTS
//

#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "MTP40C.h"
#include "SoftwareSerial.h"


unittest_setup()
{
  fprintf(stderr, "MTP40_LIB_VERSION:\t%s\n", (char *) MTP40_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(MTP40_OK                  , 0x00);
  assertEqual(MTP40_INVALID_AIR_PRESSURE, 0x01);
  assertEqual(MTP40_INVALID_GAS_LEVEL   , 0x02);
  assertEqual(MTP40_INVALID_ADDRESS     , 0xFF);
}


unittest(test_getType)
{
  MTP40C sensorC = MTP40C(&Serial);
  assertEqual(2, sensorC.getType());

  MTP40D sensorD = MTP40D(&Serial);
  assertEqual(3, sensorD.getType());

  MTP40 sensor = MTP40(&Serial);
  assertEqual(255, sensor.getType());

}


unittest(test_begin)
{
  MTP40C sensor = MTP40C(&Serial);

  for (int addr = 248; addr < 256; addr++)
  {
    assertFalse(sensor.begin(addr));
  }
  // assertTrue(sensor.begin());  blocks!

  // assertFalse(sensor.isConnected());  blocks!
}


unittest(test_address)
{
  MTP40C sensor = MTP40C(&Serial);
  // assertTrue(sensor.begin());  blocks!

  // assertEqual(0x64, sensor.getAddress());
  for (int addr = 248; addr < 256; addr++)
  {
    assertFalse(sensor.setAddress(addr));
  }
  // assertFalse(sensor.setAddress(50));
}


unittest(test_air_pressure)
{
  MTP40C sensor = MTP40C(&Serial);
  // assertTrue(sensor.begin());    // default address

  // assertEqual(-999, sensor.getAirPressureReference());

  assertFalse(sensor.setAirPressureReference(600.0));
  assertFalse(sensor.setAirPressureReference(1200.0));
  // assertFalse(sensor.setAirPressureReference(1000.0));
}


unittest(test_gas_concentration)
{
  MTP40C sensor = MTP40C(&Serial);
  // assertTrue(sensor.begin());

  // assertEqual(0, sensor.getGasConcentration());
}


unittest(test_single_point_correction)
{
  MTP40C sensor = MTP40C(&Serial);
  // assertTrue(sensor.begin());

  // assertFalse(sensor.getSinglePointCorrectionReady());

  assertFalse(sensor.setSinglePointCorrection(399.9));
  assertFalse(sensor.setSinglePointCorrection(5000.1));
  // assertFalse(sensor.setSinglePointCorrection(1000.0));
}


unittest(test_self_calibration)
{
  MTP40C sensor = MTP40C(&Serial);
  // assertTrue(sensor.begin());    // default address

  // assertFalse(sensor.openSelfCalibration());
  // assertFalse(sensor.closeSelfCalibration());
  // assertEqual(0x02, sensor.getSelfCalibrationStatus());
}


unittest(test_self_calibration_hours)
{
  MTP40C sensor = MTP40C(&Serial);
  // assertTrue(sensor.begin());    // default address

  assertFalse(sensor.setSelfCalibrationHours(23));
  assertFalse(sensor.setSelfCalibrationHours(721));
  // assertFalse(sensor.setSelfCalibrationHours(100));
  // assertEqual(0xFFFF, sensor.getSelfCalibrationHours());
}


unittest_main()

// --------
