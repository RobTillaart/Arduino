//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-05-18
// PURPOSE: unit tests for the INA226 library
//          https://github.com/RobTillaart/INA226
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


#include "INA226.h"



unittest_setup()
{
  fprintf(stderr, "\n INA226_LIB_VERSION: %s\n", (char *) INA226_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constructor)
{

  INA226 INA(0x40);

  Wire.begin();
  assertTrue(INA.begin());
  assertTrue(INA.isConnected());
  assertEqual(0x40, INA.getAddress());

  assertFalse(INA.isCalibrated());
}


unittest(test_constants)
{
  assertEqual(0x8000, INA226_SHUNT_OVER_VOLTAGE);
  assertEqual(0x4000, INA226_SHUNT_UNDER_VOLTAGE);
  assertEqual(0x2000, INA226_BUS_OVER_VOLTAGE);
  assertEqual(0x1000, INA226_BUS_UNDER_VOLTAGE);
  assertEqual(0x0800, INA226_POWER_OVER_LIMIT);
  assertEqual(0x0400, INA226_CONVERSION_READY);

  assertEqual(0x0010, INA226_ALERT_FUNCTION_FLAG);
  assertEqual(0x0008, INA226_CONVERSION_READY_FLAG);
  assertEqual(0x0004, INA226_MATH_OVERFLOW_FLAG);
  assertEqual(0x0002, INA226_ALERT_POLARITY_FLAG);
  assertEqual(0x0001, INA226_ALERT_LATCH_ENABLE_FLAG);

  assertEqual(0x0000, INA226_ERR_NONE);
  assertEqual(0x8000, INA226_ERR_SHUNTVOLTAGE_HIGH);
  assertEqual(0x8001, INA226_ERR_MAXCURRENT_LOW);
  assertEqual(0x8002, INA226_ERR_SHUNT_LOW);

  assertEqualFloat(0.001, INA226_MINIMAL_SHUNT_OHM, 0.0001);
}


unittest(test_enum_setAverage)
{
  assertEqual(0, INA226_1_SAMPLE);
  assertEqual(1, INA226_4_SAMPLES);
  assertEqual(2, INA226_16_SAMPLES);
  assertEqual(3, INA226_64_SAMPLES);
  assertEqual(4, INA226_128_SAMPLES);
  assertEqual(5, INA226_256_SAMPLES);
  assertEqual(6, INA226_512_SAMPLES);
  assertEqual(7, INA226_1024_SAMPLES);
}


unittest(test_enum_BVCT_SVCT)
{
  assertEqual(0, INA226_140_us );
  assertEqual(1, INA226_204_us );
  assertEqual(2, INA226_332_us );
  assertEqual(3, INA226_588_us );
  assertEqual(4, INA226_1100_us);
  assertEqual(5, INA226_2100_us);
  assertEqual(6, INA226_4200_us);
  assertEqual(7, INA226_8300_us);
}


unittest(test_core_functions)
{
  INA226 INA(0x40);

  Wire.begin();
  //  assertTrue(INA.begin());

  fprintf(stderr, "need mock up\n");
  /*
  fprintf(stderr, "%f\n", INA.getShuntVoltage());
  fprintf(stderr, "%f\n", INA.getBusVoltage());
  fprintf(stderr, "%f\n", INA.getPower());
  fprintf(stderr, "%f\n", INA.getCurrent());
  */
}


unittest(test_configuration)
{
  INA226 INA(0x40);

  Wire.begin();
  //  assertTrue(INA.begin());

  //  only errors can be tested
  assertFalse(INA.setAverage(8));
  assertFalse(INA.setAverage(255));

  assertFalse(INA.setBusVoltageConversionTime(8));
  assertFalse(INA.setBusVoltageConversionTime(255));

  assertFalse(INA.setShuntVoltageConversionTime(8));
  assertFalse(INA.setShuntVoltageConversionTime(255));
}


unittest(test_calibration)
{
  INA226 INA(0x40);

  Wire.begin();
  //  assertTrue(INA.begin());

  assertEqual(INA226_ERR_NONE, INA.setMaxCurrentShunt(30, 0.002));
  assertEqual(INA226_ERR_NONE, INA.setMaxCurrentShunt(1,  0.05));
  assertEqual(INA226_ERR_NONE, INA.setMaxCurrentShunt(1,  0.080));

  assertEqual(INA226_ERR_SHUNTVOLTAGE_HIGH, INA.setMaxCurrentShunt(82.0, 0.001));
  assertEqual(INA226_ERR_SHUNTVOLTAGE_HIGH, INA.setMaxCurrentShunt(41.0, 0.002));
  assertEqual(INA226_ERR_SHUNTVOLTAGE_HIGH, INA.setMaxCurrentShunt(20.5, 0.004));
  assertEqual(INA226_ERR_SHUNTVOLTAGE_HIGH, INA.setMaxCurrentShunt(1.1, 0.080));

  assertEqual(INA226_ERR_MAXCURRENT_LOW,    INA.setMaxCurrentShunt(0.0009));
  assertEqual(INA226_ERR_MAXCURRENT_LOW,    INA.setMaxCurrentShunt(0));
  assertEqual(INA226_ERR_MAXCURRENT_LOW,    INA.setMaxCurrentShunt(-1));
  assertEqual(INA226_ERR_SHUNT_LOW,         INA.setMaxCurrentShunt(10, 0));
  assertEqual(INA226_ERR_SHUNT_LOW,         INA.setMaxCurrentShunt(10, 0.0009));
}


unittest(test_setMode)
{
  INA226 INA(0x40);

  Wire.begin();
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

