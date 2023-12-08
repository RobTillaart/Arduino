//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-06-24
// PURPOSE: unit tests for Arduino library for SGP30 environment sensor.
//          https://github.com/RobTillaart/SGP30
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


#include "SGP30.h"



unittest_setup()
{
  fprintf(stderr, "SGP30_LIB_VERSION: %s\n", (char *) SGP30_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  SGP30 SGP;

  Wire.begin();
  assertTrue(SGP.begin());
  assertTrue(SGP.isConnected());

  assertEqual(0x00, SGP.lastMeasurement());
  assertEqual(0x00, SGP.lastError());
}


unittest(test_constants)
{
  assertEqual(SGP30_OK,        0x00);
  assertEqual(SGP30_ERROR_CRC, 0xFF);
  assertEqual(SGP30_ERROR_I2C, 0xFE);
}


unittest(test_defaults_core)
{
  SGP30 SGP;
  
  Wire.begin();
  assertEqual(0x00, SGP.getCO2());
  assertEqual(0x00, SGP.getTVOC());
  assertEqual(0x00, SGP.getH2_raw());
  assertEqual(0x00, SGP.getEthanol_raw());
  assertEqualFloat(6.71302e+10, SGP.getH2(), 1e7);
  assertEqualFloat(1.86462e+15, SGP.getEthanol(), 1e12);
}


unittest(test_sref_H2)
{
  SGP30 SGP;

  Wire.begin();
  assertEqual(13119, SGP.getSrefH2());

  SGP.setSrefH2(0);
  assertEqual(0, SGP.getSrefH2());

  SGP.setSrefH2(10000);
  assertEqual(10000, SGP.getSrefH2());

  SGP.setSrefH2();
  assertEqual(13119, SGP.getSrefH2());
}


unittest(test_sref_Ethanol)
{
  SGP30 SGP;

  Wire.begin();
  assertEqual(18472, SGP.getSrefEthanol());

  SGP.setSrefEthanol(0);
  assertEqual(0, SGP.getSrefEthanol());

  SGP.setSrefEthanol(10000);
  assertEqual(10000, SGP.getSrefEthanol());

  SGP.setSrefEthanol();
  assertEqual(18472, SGP.getSrefEthanol());
}


unittest_main()


//  -- END OF FILE --
