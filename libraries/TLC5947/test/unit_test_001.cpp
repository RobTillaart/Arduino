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
  TLC5947 tlc1(1, 13, 12, 11, 10);

  assertTrue(tlc1.begin());
  assertEqual(24, tlc1.getChannels());

  TLC5947 tlc(21, 13, 12, 11, 10);

  assertTrue(tlc.begin());
  assertEqual(504, tlc.getChannels());
}


unittest(test_setPWM_I)
{
  TLC5947 tlc(1, 13, 12, 11, 10);
  tlc.begin();
  assertEqual(24, tlc.getChannels());

  for (uint8_t channel = 0; channel < 24; channel++)
  {
    tlc.setPWM(channel, channel * 170);
    assertEqual(tlc.getPWM(channel), channel * 170);
  }
}


unittest(test_setPWM_II)
{
  TLC5947 tlc(1, 13, 12, 11, 10);
  tlc.begin();
  assertEqual(24, tlc.getChannels());

  tlc.setAll(421);
  for (uint8_t channel = 0; channel < 24; channel++)
  {
    assertEqual(tlc.getPWM(channel), 421);
  }
}


unittest(test_setPercentage_I)
{
  TLC5947 tlc(1, 13, 12, 11, 10);
  tlc.begin();

  for (uint8_t channel = 0; channel < 24; channel++)
  {
    float val = channel * 4.3478;
    tlc.setPercentage(channel, val);
    float rval = tlc.getPercentage(channel);
    assertEqualFloat(rval, val, 0.02);

    fprintf(stderr, "%d\t%.4f\d%.4f\n", channel, val, rval);
  }
}


unittest(test_setPercentage_II)
{
  TLC5947 tlc(2, 13, 12, 11, 10);
  tlc.begin();
  assertEqual(48, tlc.getChannels());

  tlc.setPercentageAll(12.34);
  for (uint8_t channel = 0; channel < tlc.getChannels(); channel += 2)
  {
    assertEqualFloat(tlc.getPercentage(channel), 12.34, 0.02);
  }
}


unittest(test_setRGB)
{
  TLC5947 tlc(1, 13, 12, 11, 10);
  tlc.begin();

  for (uint8_t led = 0; led < 8; led++)
  {
    tlc.setRGB(led, 100, 200, 300);
    uint16_t R, G, B;
    tlc.getRGB(led, R, G, B);
    assertEqual(R, 100);
    assertEqual(G, 200);
    assertEqual(B, 300);
  }
}



unittest_main()


//  -- END OF FILE --

