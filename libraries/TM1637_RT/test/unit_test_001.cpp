//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-04-16
// PURPOSE: unit tests for the TM1637 library
//          https://github.com/RobTillaart/TM_1637_RT
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
#include "TM1637.h"



unittest_setup()
{
  fprintf(stderr, "TM1637_LIB_VERSION: %s\n", (char *) TM1637_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_begin)
{
  TM1637 TM;
  TM.begin(2, 3, 6);

  TM.displayClear();
  // TODO real tests....
  assertEqual(1, 1);
}


unittest(test_brightness)
{
  TM1637 TM;
  TM.begin(2, 3, 6);
  
  for (uint8_t b = 0; b < 8; b++)
  {
    TM.setBrightness(b);
    uint8_t bb = TM.getBrightness();
    assertEqual(b, bb);
  }
  for (uint8_t b = 8; b < 10; b++)
  {
    TM.setBrightness(b);
    uint8_t bb = TM.getBrightness();
    assertEqual(7, bb);
  }
}


unittest(test_set_bit_delay)
{
  TM1637 TM;
  TM.begin(2, 3, 6);
  
  for (uint8_t b = 0; b < 100; b += 10)
  {
    TM.setBitDelay(b);
    uint8_t bb = TM.getBitDelay();
    assertEqual(b, bb);
  }

}


unittest_main()


//  -- END OF FILE --

