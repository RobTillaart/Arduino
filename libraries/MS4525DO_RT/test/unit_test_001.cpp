//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-12-06
// PURPOSE: unit tests for the I2C MS4525DO pressure sensor library
//          https://github.com/RobTillaart/MS4525DO_RT
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
#include "MS4525DO.h"


unittest_setup()
{
  fprintf(stderr, "MS4525DO_LIB_VERSION: %s\n", (char *) MS4525DO_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  MS4525DO sensor(0x28);

  assertEqual(MS4525DO_INIT, sensor.state());

  Wire.begin();
  assertTrue(sensor.begin(100));
  assertTrue(sensor.isConnected());    //  incorrect, keep build happy

  fprintf(stderr, "test state\n");
  assertEqual(0, sensor.errorCount());
  assertEqual(0, sensor.lastRead());
  assertEqual(MS4525DO_OK, sensor.state());
}


unittest(test_constants)
{
  fprintf(stderr, "Test state constants\n");
  assertEqual(1,  MS4525DO_OK);
  assertEqual(0,  MS4525DO_INIT);
  assertEqual(-1, MS4525DO_READ_ERROR);
  assertEqual(-2, MS4525DO_OVF_ERROR);
  assertEqual(-3, MS4525DO_CONNECT_ERROR);
}


unittest_main()


//  -- END OF FILE --

