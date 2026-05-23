//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-05-18
// PURPOSE: unit tests for the INA2227 library
//          https://github.com/RobTillaart/INA2227
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


#include "INA2227.h"



unittest_setup()
{
  fprintf(stderr, "\n INA2227_LIB_VERSION: %s\n", (char *) INA2227_LIB_VERSION);
}

unittest_teardown()
{
}


//unittest(test_constructor)
//{
//INA2227 INA(0x40);
//
//Wire.begin();
//assertTrue(INA.begin());
//assertTrue(INA.isConnected());
//assertEqual(0x40, INA.getAddress());
//
//assertFalse(INA.isCalibrated());
//}


unittest(test_constants)
{
  assertEqual(1, INA2227_SHUNT_OVER_VOLTAGE);
  assertEqual(2, INA2227_SHUNT_UNDER_VOLTAGE);
  assertEqual(3, INA2227_BUS_OVER_VOLTAGE);
  assertEqual(4, INA2227_BUS_UNDER_VOLTAGE);
  assertEqual(5, INA2227_POWER_OVER_LIMIT);

  assertEqual(0x0000, INA2227_ERR_NONE);
  assertEqual(0x8000, INA2227_ERR_SHUNTVOLTAGE_HIGH);
  assertEqual(0x8001, INA2227_ERR_MAXCURRENT_LOW);
  assertEqual(0x8002, INA2227_ERR_SHUNT_LOW);

  assertEqualFloat(0.001, INA2227_MINIMAL_SHUNT, 0.0001);
}


unittest(test_enum_setAverage)
{
  assertEqual(0, INA2227_1_SAMPLE);
  assertEqual(1, INA2227_4_SAMPLES);
  assertEqual(2, INA2227_16_SAMPLES);
  assertEqual(3, INA2227_64_SAMPLES);
  assertEqual(4, INA2227_128_SAMPLES);
  assertEqual(5, INA2227_256_SAMPLES);
  assertEqual(6, INA2227_512_SAMPLES);
  assertEqual(7, INA2227_1024_SAMPLES);
}


unittest(test_enum_BVCT_SVCT)
{
  assertEqual(0, INA2227_140_us );
  assertEqual(1, INA2227_204_us );
  assertEqual(2, INA2227_332_us );
  assertEqual(3, INA2227_588_us );
  assertEqual(4, INA2227_1100_us);
  assertEqual(5, INA2227_2100_us);
  assertEqual(6, INA2227_4200_us);
  assertEqual(7, INA2227_8300_us);
}


// unittest(test_core_functions)
// {
  // INA2227 INA(0x40);

  // Wire.begin();
  // assertTrue(INA.begin());

  // fprintf(stderr, "need mock up\n");
  // /*
  // fprintf(stderr, "%f\n", INA.getShuntVoltage());
  // fprintf(stderr, "%f\n", INA.getBusVoltage());
  // fprintf(stderr, "%f\n", INA.getPower());
  // fprintf(stderr, "%f\n", INA.getCurrent());
  // */
// }


unittest(test_configuration)
{
  INA2227 INA(0x40);

  //  Wire.begin();
  //  assertTrue(INA.begin());

  //  only errors can be tested
  assertFalse(INA.setAverage(8));
  assertFalse(INA.setAverage(255));

  assertFalse(INA.setBusVoltageConversionTime(8));
  assertFalse(INA.setBusVoltageConversionTime(255));

  assertFalse(INA.setShuntVoltageConversionTime(8));
  assertFalse(INA.setShuntVoltageConversionTime(255));
}


/*
unittest(test_calibration)
{
  INA2227 INA(0x40);

  //  Wire.begin();
  //  assertTrue(INA.begin());

  assertEqual(INA2227_ERR_NONE, INA.setMaxCurrentShunt(30, 0.002));
  assertEqual(INA2227_ERR_NONE, INA.setMaxCurrentShunt(1,  0.05));
  assertEqual(INA2227_ERR_NONE, INA.setMaxCurrentShunt(1,  0.080));

  assertEqual(INA2227_ERR_SHUNTVOLTAGE_HIGH, INA.setMaxCurrentShunt(80.1, 0.001));
  assertEqual(INA2227_ERR_SHUNTVOLTAGE_HIGH, INA.setMaxCurrentShunt(40.1, 0.002));
  assertEqual(INA2227_ERR_SHUNTVOLTAGE_HIGH, INA.setMaxCurrentShunt(20.1, 0.004));
  assertEqual(INA2227_ERR_SHUNTVOLTAGE_HIGH, INA.setMaxCurrentShunt(1.1, 0.080));

  assertEqual(INA2227_ERR_MAXCURRENT_LOW,    INA.setMaxCurrentShunt(0.0009));
  assertEqual(INA2227_ERR_MAXCURRENT_LOW,    INA.setMaxCurrentShunt(0));
  assertEqual(INA2227_ERR_MAXCURRENT_LOW,    INA.setMaxCurrentShunt(-1));
  assertEqual(INA2227_ERR_SHUNT_LOW,         INA.setMaxCurrentShunt(10, 0));
  assertEqual(INA2227_ERR_SHUNT_LOW,         INA.setMaxCurrentShunt(10, 0.0009));
}
*/


unittest(test_setMode)
{
  INA2227 INA(0x40);

  //  Wire.begin();
  //  assertTrue(INA.begin());

  //  only errors can be tested
  assertFalse(INA.setMode(8));
  assertFalse(INA.setMode(255));
  assertFalse(INA.setMode(-1));
  /*
  assertTrue(INA.shutDown());
  assertTrue(INA.setModeShuntTrigger());
  assertTrue(INA.setModeBusTrigger());
  assertTrue(INA.setModeShuntBusTrigger());
  assertTrue(INA.setModeShuntContinuous());
  assertTrue(INA.setModeBusContinuous());
  assertTrue(INA.setModeShuntBusContinuous());
  */
}


unittest_main()


//  -- END OF FILE --

