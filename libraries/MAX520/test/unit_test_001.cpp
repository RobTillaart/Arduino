//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2024-03-06
// PURPOSE: unit tests for the MAX520/521 4/8 channel DAC
//          https://github.com/RobTillaart/MAX520
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
#include "MAX520.h"


MAX520 mx(0x38);


unittest_setup()
{
  fprintf(stderr, "MAX520_LIB_VERSION: %s\n", (char *) MAX520_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_begin)
{
  MAX520 mx0(0x38);
  Wire.begin();
  mx0.begin();
  assertEqual(4, mx0.getChannels());


  MAX521 mx1(0x38);
  Wire.begin();
  mx1.begin();
  assertEqual(8, mx1.getChannels());
}


unittest_main()


//  -- END OF FILE --

