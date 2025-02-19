//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-18
// PURPOSE: unit tests for the INA260 library
//          https://github.com/RobTillaart/INA260
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


#include "INA260.h"



unittest_setup()
{
  fprintf(stderr, "\n INA260_LIB_VERSION: %s\n", (char *) INA260_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constructor)
{

  INA260 INA(0x40);

  Wire.begin();
  assertTrue(INA.begin());
  assertTrue(INA.isConnected());
  assertEqual(0x40, INA.getAddress());
}


unittest(test_constants)
{
  assertEqual(0x8000, INA260_SHUNT_OVER_CURRENT);
  assertEqual(0x4000, INA260_SHUNT_UNDER_CURRENT);
  assertEqual(0x2000, INA260_BUS_OVER_VOLTAGE);
  assertEqual(0x1000, INA260_BUS_UNDER_VOLTAGE);
  assertEqual(0x0800, INA260_POWER_OVER_LIMIT);
  assertEqual(0x0400, INA260_CONVERSION_READY);

  assertEqual(0x0010, INA260_ALERT_FUNCTION_FLAG);
  assertEqual(0x0008, INA260_CONVERSION_READY_FLAG);
  assertEqual(0x0004, INA260_MATH_OVERFLOW_FLAG);
  assertEqual(0x0002, INA260_ALERT_POLARITY_FLAG);
  assertEqual(0x0001, INA260_ALERT_LATCH_ENABLE_FLAG);
}


unittest(test_enum_setAverage)
{
  assertEqual(0, INA260_1_SAMPLE);
  assertEqual(1, INA260_4_SAMPLES);
  assertEqual(2, INA260_16_SAMPLES);
  assertEqual(3, INA260_64_SAMPLES);
  assertEqual(4, INA260_128_SAMPLES);
  assertEqual(5, INA260_256_SAMPLES);
  assertEqual(6, INA260_512_SAMPLES);
  assertEqual(7, INA260_1024_SAMPLES);
}


unittest(test_enum_BVCT_SVCT)
{
  assertEqual(0, INA260_140_us );
  assertEqual(1, INA260_204_us );
  assertEqual(2, INA260_332_us );
  assertEqual(3, INA260_588_us );
  assertEqual(4, INA260_1100_us);
  assertEqual(5, INA260_2100_us);
  assertEqual(6, INA260_4200_us);
  assertEqual(7, INA260_8300_us);
}


unittest(test_core_functions)
{
  INA260 INA(0x40);

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
  INA260 INA(0x40);

  Wire.begin();
  //  assertTrue(INA.begin());

  //  only errors can be tested
  assertFalse(INA.setAverage(8));
  assertFalse(INA.setAverage(255));

  assertFalse(INA.setBusVoltageConversionTime(8));
  assertFalse(INA.setBusVoltageConversionTime(255));

  assertFalse(INA.setShuntCurrentConversionTime(8));
  assertFalse(INA.setShuntCurrentConversionTime(255));
}


unittest(test_setMode)
{
  INA260 INA(0x40);

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

