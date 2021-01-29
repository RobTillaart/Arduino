//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-01
// PURPOSE: unit tests for the I2C mcp9808 temperature sensor
//          https://github.com/RobTillaart/MCP9808_RT
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
#include "mcp9808.h"


unittest_setup()
{
}

unittest_teardown()
{
}


// TODO more can be tested if there is a Godmode->Wire stub

unittest(test_constructor)
{
  fprintf(stderr, "VERSION: %s\n", "-");

  MCP9808 ts(24);
  assertTrue(ts.setAddress(24, &Wire) );
  assertTrue(ts.isConnected());
}

unittest(test_offset)
{
  MCP9808 ts(24);
  for (int i = -10; i < 10; i++)
  {
    ts.setOffset(i * 0.1);
    fprintf(stderr, "%f\t", i * 0.1);
    assertEqualFloat(i * 0.1, ts.getOffset(), 0.0001);
  }
}

unittest_main()

// --------
