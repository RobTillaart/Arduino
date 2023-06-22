//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-06-17
// PURPOSE: unit tests for the TLC5947 library
//          https://github.com/RobTillaart/TLC5947
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
#include "TLC5947.h"



unittest_setup()
{
  fprintf(stderr, "TLC5947_LIB_VERSION: %s\n", (char *) TLC5947_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_begin)
{
  TLC5947 tlc(13, 12, 11, 10);

  assertTrue(tlc.begin());
}


unittest(test_setPWM_I)
{
  TLC5947 tlc(13, 12, 11, 10);
  tlc.begin();

  for (uint8_t chan = 0; chan < 24; chan++)
  {
    tlc.setPWM(chan, chan * 170);
    assertEqual(tlc.getPWM(chan), chan * 170);
  }
}


unittest(test_setPWM_II)
{
  TLC5947 tlc(13, 12, 11, 10);
  tlc.begin();

  tlc.setAll(421);
  for (uint8_t chan = 0; chan < 24; chan++)
  {
    assertEqual(tlc.getPWM(chan), 421);
  }
}


unittest(test_setPercentage_I)
{
  TLC5947 tlc(13, 12, 11, 10);
  tlc.begin();

  for (uint8_t chan = 0; chan < 24; chan++)
  {
    float val = chan * 4.3478;
    tlc.setPercentage(chan, val);
    float rval = tlc.getPercentage(chan);
    assertEqualFloat(rval, val, 0.02);

    fprintf(stderr, "%d\t%.4f\d%.4f\n", chan, val, rval);
  }
}


unittest(test_setPercentage_II)
{
  TLC5947 tlc(13, 12, 11, 10);
  tlc.begin();

  tlc.setPercentageAll(12.34);
  for (uint8_t chan = 0; chan < 24; chan++)
  {
    assertEqualFloat(tlc.getPercentage(chan), 12.34, 0.02);
  }
}



unittest_main()


//  -- END OF FILE --

