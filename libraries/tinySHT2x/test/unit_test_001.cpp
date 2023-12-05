//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-12-29
// PURPOSE: unit tests for the timing libraty
//          https://github.com/RobTillaart/timing
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
#include "tinySHT2x.h"


unittest_setup()
{
  fprintf(stderr, "TINY_SHT2x_LIB_VERSION: %s\n", (char *) TINY_SHT2x_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constant)
{
  assertEqual(-999, TINY_SHT2x_NO_VALUE);
}


unittest(test_constructor)
{
  tinySHT2x sht;

  Wire.begin();

  sht.begin();
  assertTrue(sht.reset());
  //  need godmode for these
  //  assertEqualFloat(TINY_SHT2x_NO_VALUE, sht.getTemperature(), 0.01);
  //  assertEqualFloat(TINY_SHT2x_NO_VALUE, sht.getHumidity(), 0.01);
}


unittest_main()


//  -- END OF FILE --

