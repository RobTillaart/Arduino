//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-05-18
// PURPOSE: unit tests for the INA219 library
//          https://github.com/RobTillaart/INA219
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


#include "INA219.h"



unittest_setup()
{
  fprintf(stderr, "\n INA219_LIB_VERSION: %s\n", (char *) INA219_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  INA219 INA(0x40);

  Wire.begin();
  assertTrue(INA.begin());
  assertTrue(INA.isConnected());
  assertEqual(0x40, INA.getAddress());

  //  default is not calibrated.
  assertFalse(INA.isCalibrated());
  assertEqualFloat(0.0, INA.getCurrentLSB(), 0.001);
  assertEqualFloat(0.0, INA.getShunt(), 0.001);
  assertEqualFloat(0.0, INA.getMaxCurrent(), 0.001);

  //  fails but will set the vars
  INA.setMaxCurrentShunt(5, 0.002);

  assertTrue(INA.isCalibrated());
  assertEqualFloat(5.0/32768, INA.getCurrentLSB(), 0.0001);
  assertEqualFloat(0.002,     INA.getShunt(), 0.001);
  assertEqualFloat(5.000,     INA.getMaxCurrent(), 0.001);
}


unittest(test_core_functions)
{
  INA219 INA(0x40);
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
  INA219 INA(0x40);
  //  assertTrue(INA.begin());

  //  only errors can be tested
  assertFalse(INA.setBusVoltageRange(33));
  assertFalse(INA.setGain(3));
  assertFalse(INA.setGain(5));
  assertFalse(INA.setGain(6));
  assertFalse(INA.setGain(7));
  assertFalse(INA.setGain(9));
  assertFalse(INA.setBusADC(16));
  assertFalse(INA.setShuntADC(16));
}


unittest(test_calibration)
{
  INA219 INA(0x40);
  //  assertTrue(INA.begin());

  //  only errors can be tested
  assertFalse(INA.setMaxCurrentShunt(0.0009));
  assertFalse(INA.setMaxCurrentShunt(0));
  assertFalse(INA.setMaxCurrentShunt(-1));
  assertFalse(INA.setMaxCurrentShunt(10, 0));
  assertFalse(INA.setMaxCurrentShunt(10, 0.0009));
}


unittest_main()


//  -- END OF FILE --

