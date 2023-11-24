//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-22
// PURPOSE: unit tests for the I2C_24LC1025 library
//          https://github.com/RobTillaart/I2C_24LC1025
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
#include "I2C_24LC1025.h"


unittest_setup()
{
  fprintf(stderr, "I2C_24LC1025_LIB_VERSION: %s\n", (char *) I2C_24LC1025_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(131072, I2C_DEVICESIZE_24LC1025);
  assertEqual(   128, I2C_PAGESIZE_24LC1025);
}


unittest(test_constructor)
{
  Wire.resetMocks();

  I2C_24LC1025 EE(0x50);

  Wire.begin();
  assertTrue(EE.begin());

  assertEqual(1, 1);
}


unittest_main()


//  -- END OF FILE --

