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
  fprintf(stderr, "M62429_VERSION: %s\n", (char *) M62429_VERSION);
}


unittest_teardown()
{
}


unittest(test_setVolume)
{
  uint8_t dataPin = 6;
  uint8_t clockPin = 7;

  M62429 AMP;
  AMP.begin(dataPin, clockPin);

  fprintf(stderr, "\nset get volume(0)\n");
  for (int vol = 0; vol < 10; vol++)
  {
    AMP.setVolume(0, vol);
    assertEqual(vol, AMP.getVolume(0));
  }

  fprintf(stderr, "\nset get volume(1)\n");
  for (int vol = 10; vol < 20; vol++)
  {
    AMP.setVolume(1, vol);
    assertEqual(vol, AMP.getVolume(1));
  }

  fprintf(stderr, "\nset get volume(2)\n");
  for (int vol = 30; vol < 40; vol++)
  {
    AMP.setVolume(2, vol);
    assertEqual(vol, AMP.getVolume(0));
    assertEqual(vol, AMP.getVolume(1));
  }

  fprintf(stderr, "\nerror volume(3)\n");
  assertEqual(M62429_CHANNEL_ERROR, AMP.setVolume(3, 25));
}


unittest(test_incr_decr)
{
  uint8_t dataPin = 6;
  uint8_t clockPin = 7;

  M62429 AMP;
  AMP.begin(dataPin, clockPin);

  fprintf(stderr, "\nincr decr channel 0\n");
  AMP.setVolume(2, 0);
  for (int i = 0; i < 10; i++) AMP.incr(0);
  assertEqual(10, AMP.getVolume(0));
  assertEqual(0,  AMP.getVolume(1));
  for (int i = 0; i < 5; i++) AMP.decr(0);
  assertEqual(5, AMP.getVolume(0));
  assertEqual(0, AMP.getVolume(1));

  fprintf(stderr, "\nincr decr channel 1\n");
  AMP.setVolume(2, 0);
  for (int i = 0; i < 10; i++) AMP.incr(1);
  assertEqual(0,  AMP.getVolume(0));
  assertEqual(10, AMP.getVolume(1));
  for (int i = 0; i < 5; i++) AMP.decr(1);
  assertEqual(0, AMP.getVolume(0));
  assertEqual(5, AMP.getVolume(1));

  fprintf(stderr, "\nincr decr channel 2\n");
  AMP.setVolume(2, 0);
  for (int i = 0; i < 10; i++) AMP.incr();  // 2 is default
  assertEqual(10, AMP.getVolume(0));
  assertEqual(10, AMP.getVolume(1));
  for (int i = 0; i < 5; i++) AMP.decr();
  assertEqual(5, AMP.getVolume(0));
  assertEqual(5, AMP.getVolume(1));

  fprintf(stderr, "\nincr decr channel error\n");
  assertEqual(M62429_CHANNEL_ERROR, AMP.incr(3));
  assertEqual(M62429_CHANNEL_ERROR, AMP.decr(3));
}


unittest(test_average)
{
  uint8_t dataPin = 6;
  uint8_t clockPin = 7;

  M62429 AMP;
  AMP.begin(dataPin, clockPin);

  AMP.setVolume(0, 10);
  AMP.setVolume(1, 20);
  assertEqual(10, AMP.getVolume(0));
  assertEqual(20, AMP.getVolume(1));
  AMP.average();
  assertEqual(15, AMP.getVolume(0));
  assertEqual(15, AMP.getVolume(1));
}


unittest(test_mute)
{
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

  assertEqual(M62429_OK, AMP.setVolume(0, 10));
  assertEqual(10, AMP.getVolume(0));

  fprintf(stderr, "mute on\n");
  AMP.muteOn();
  assertTrue(AMP.isMuted());

  assertEqual(M62429_MUTED, AMP.setVolume(0, 20));
  assertEqual(10, AMP.getVolume(0));

  assertEqual(M62429_MUTED, AMP.setVolume(0, 0));
  assertEqual(10, AMP.getVolume(0));

  assertEqual(M62429_MUTED, AMP.incr());
  assertEqual(10, AMP.getVolume(0));

  assertEqual(M62429_MUTED, AMP.decr());
  assertEqual(10, AMP.getVolume(0));

  assertEqual(M62429_MUTED, AMP.average());
  assertEqual(10, AMP.getVolume(0));

  AMP.muteOff();
  assertFalse(AMP.isMuted());
  assertEqual(M62429_OK, AMP.setVolume(0, 20));
  assertEqual(20, AMP.getVolume(0));

}


unittest_main()

// --------
