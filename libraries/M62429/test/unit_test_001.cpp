//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-30
// PURPOSE: unit tests for the M62429 volume IC
//          https://github.com/RobTillaart/M62429
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
#include "M62429.h"



unittest_setup()
{
}

unittest_teardown()
{
}

/*
unittest(test_new_operator)
{
  assertEqualINF(exp(800));
  assertEqualINF(0.0/0.0);
  assertEqualINF(42);
  
  assertEqualNAN(INFINITY - INFINITY);
  assertEqualNAN(0.0/0.0);
  assertEqualNAN(42);
}
*/

unittest(test_all)
{
  fprintf(stderr, "VERSION: %s\n", M62429_VERSION);

  uint8_t dataPin = 6;
  uint8_t clockPin = 7;
  
  M62429 AMP;
  AMP.begin(dataPin, clockPin);

  fprintf(stderr, "mute on off\n");
  assertFalse(AMP.isMuted());
  AMP.muteOn();
  assertTrue(AMP.isMuted());
  AMP.muteOff();
  assertFalse(AMP.isMuted());

  fprintf(stderr, "set get volume\n");
  for (int vol = 0; vol < 10; vol++)
  {
    AMP.setVolume(0, vol);
    assertEqual(vol, AMP.getVolume(0));
  }
  for (int vol = 10; vol < 20; vol++)
  {
    AMP.setVolume(1, vol);
    assertEqual(vol, AMP.getVolume(1));
  }

  for (int vol = 30; vol < 40; vol++)
  {
    AMP.setVolume(2, vol);
    assertEqual(vol, AMP.getVolume(0));
    assertEqual(vol, AMP.getVolume(1));
  }

  fprintf(stderr, "incr, decr\n");
  AMP.setVolume(0, 0);
  for (int i = 0; i < 10; i++) AMP.incr();
  assertEqual(10, AMP.getVolume(0));
  for (int i = 0; i < 5; i++) AMP.decr();
  assertEqual(5, AMP.getVolume(0));
}

unittest_main()

// --------
