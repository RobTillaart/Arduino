//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-01-28
// PURPOSE: unit tests for the PIR8575 library
//          https://github.com/RobTillaart/PIR8575
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
#include "PIR8575.h"


unittest_setup()
{
  fprintf(stderr, "PIR8575_LIB_VERSION: %s\n", (char *) PIR8575_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_begin)
{
  PIR8575 PIR(0x38);

  Wire.begin();
  PIR.begin();

  uint16_t value = PIR.read16();
  assertEqual(0, value);
}


unittest(test_read)
{
  PIR8575 PIR(0x38);
  uint16_t value;

  Wire.begin();
  PIR.begin();

  for (int i = 0; i < 16; i++)
  {
    fprintf(stderr, "line %d\n", i);
    value = PIR.read(i);
    assertEqual(0, value);
  }
}


unittest_main()


//  -- END OF FILE --

