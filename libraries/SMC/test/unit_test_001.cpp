//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-23
// PURPOSE: unit tests for the Arduino library for Sliding Mode Controller
//     URL: https://github.com/RobTillaart/SMC
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
#include "SMC.h"


unittest_setup()
{
  fprintf(stderr, "SMC_LIB_VERSION: %s\n", (char *) SMC_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(SMC_LINEAR, 0);
  assertEqual(SMC_EXPONENTIAL, 1);
  assertEqual(SMC_SIMPLE, 2);
}


unittest(test_constructor)
{
  SMC smc;

  fprintf(stderr, "defaults\n");
  assertEqual(smc.getMode(), 0);
  assertEqualFloat(smc.getSetPoint(), 0, 0.01);
  assertEqualFloat(smc.getMaxValue(), 0, 0.01);
  assertEqualFloat(smc.getWeight1(), 0, 0.01);
  assertEqualFloat(smc.getWeight2(), 0, 0.01);
  
  smc.begin(50, 255, 0.5, 1.0);
  assertEqual(smc.getMode(), 0);
  assertEqualFloat(smc.getSetPoint(), 50, 0.01);
  assertEqualFloat(smc.getMaxValue(), 255, 0.01);
  assertEqualFloat(smc.getWeight1(), 0.5, 0.01);
  assertEqualFloat(smc.getWeight2(), 1.0, 0.01);
}


unittest(test_mode)
{
  SMC smc;

  assertEqual(smc.getMode(), 0);
  smc.setMode(SMC_EXPONENTIAL);
  assertEqual(smc.getMode(), 1);
  smc.setMode(SMC_SIMPLE);
  assertEqual(smc.getMode(), 2);
  smc.setMode(SMC_LINEAR);
  assertEqual(smc.getMode(), 0);
}


unittest(test_outValuePercentage)
{
  SMC smc;

  smc.begin(50, 255, 0.5, 1.0);

  smc.setMode(SMC_SIMPLE);
  assertEqualFloat(smc.outValuePercentage(25), 100, 0.01);
  assertEqualFloat(smc.outValuePercentage(46), 100, 0.01);
  assertEqualFloat(smc.outValuePercentage(47), 100, 0.01);
  assertEqualFloat(smc.outValuePercentage(48), 100, 0.01);
  assertEqualFloat(smc.outValuePercentage(49), 100, 0.01);
  assertEqualFloat(smc.outValuePercentage(50), 100, 0.01);
  assertEqualFloat(smc.outValuePercentage(51),   0, 0.01);

  smc.setMode(SMC_LINEAR);
  assertEqualFloat(smc.outValuePercentage(25), 100, 0.01);
  // assertEqualFloat(smc.outValuePercentage(46), 100, 0.01);
  // assertEqualFloat(smc.outValuePercentage(47), 100, 0.01);
  assertEqualFloat(smc.outValuePercentage(48),   0, 0.01);
  assertEqualFloat(smc.outValuePercentage(49),   0, 0.01);
  assertEqualFloat(smc.outValuePercentage(50),   0, 0.01);
  assertEqualFloat(smc.outValuePercentage(51),   0, 0.01);
}


unittest(test_getter_setter)
{
  SMC smc;

  smc.setSetPoint(75);
  assertEqualFloat(smc.getSetPoint(), 75, 0.01);
  smc.setMaxValue(102);
  assertEqualFloat(smc.getMaxValue(), 102, 0.01);
  smc.setWeights(0.25, 3.14);
  assertEqualFloat(smc.getWeight1(), 0.25, 0.01);
  assertEqualFloat(smc.getWeight2(), 3.14, 0.01);
}


unittest_main()


//  -- END OF FILE --

