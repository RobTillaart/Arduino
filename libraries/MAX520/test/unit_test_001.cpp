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


unittest(test_constructor)
{
  MAX520 mx;  //  default address
  MAX520 mx0(0X20);
  MAX520 mx1(0X21);
  MAX520 mx2(0X22);
  MAX520 mx3(0X23);

  Wire.begin();
  mx.begin();
  mx0.begin();
  mx1.begin();
  mx2.begin();
  mx3.begin();

  assertEqual(0x20, mx.getAddress());
  assertEqual(0x20, mx0.getAddress());
  assertEqual(0x21, mx1.getAddress());
  assertEqual(0x22, mx2.getAddress());
  assertEqual(0x23, mx3.getAddress());


  MAX521 mx5;
  mx5.begin();
  assertEqual(0x20, mx5.getAddress());
}


unittest(test_begin)
{
  MAX520 mx0;
  Wire.begin();
  mx0.begin();
  assertEqual(4, mx0.getChannels());
  for (int ch = 0; ch < mx0.getChannels(); ch++)
  {
    assertEqual(0, mx0.read(ch));
  }


  MAX521 mx1;
  Wire.begin();
  mx1.begin();
  assertEqual(8, mx1.getChannels());
  for (int ch = 0; ch < mx1.getChannels(); ch++)
  {
    assertEqual(0, mx1.read(ch));
  }
}


unittest_main()


//  -- END OF FILE --

