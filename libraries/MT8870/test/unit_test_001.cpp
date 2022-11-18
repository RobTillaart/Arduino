//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-02
// PURPOSE: unit tests for the MT8870
//          https://github.com/RobTillaart/MT8870
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
#include "MT8870.h"


unittest_setup()
{
  fprintf(stderr, "MT8870_LIB_VERSION: %s\n", (char *) MT8870_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  uint8_t STQ = 4, Q1 = 5, Q2 = 6, Q3 = 7, Q4 = 8;
  MT8870 DTMF;

  DTMF.begin(STQ, Q1, Q2, Q3, Q4);

  assertFalse(DTMF.available());
}


unittest(test_read)
{
  GodmodeState* state = GODMODE();
  state->reset();
  
  uint8_t STQ = 4, Q1 = 5, Q2 = 6, Q3 = 7, Q4 = 8;
  MT8870 DTMF;

  DTMF.begin(STQ, Q1, Q2, Q3, Q4);
  assertFalse(DTMF.available());
  state->digitalPin[STQ] = 1;
  assertTrue(DTMF.available());

  state->digitalPin[Q1] = 1;
  state->digitalPin[Q2] = 0;
  state->digitalPin[Q3] = 0;
  state->digitalPin[Q4] = 1;
  assertEqual('9', DTMF.read());

  state->digitalPin[Q1] = 1;        // 1 +
  state->digitalPin[Q2] = 0;        // 
  state->digitalPin[Q3] = 1;        // 4 +
  state->digitalPin[Q4] = 1;        // 8 == 13
  assertEqual(13, DTMF.readRaw());
  assertEqual(13, DTMF.lastRaw());

  state->digitalPin[STQ] = 0;   // not available
  state->digitalPin[Q1] = 1;
  state->digitalPin[Q2] = 0;
  state->digitalPin[Q3] = 1;
  state->digitalPin[Q4] = 1;
  assertEqual(255, DTMF.readRaw());
  
  fprintf(stderr, "loop over 16 possible values\n");
  for (int i = 0; i < 16; i++)
  {
    fprintf(stderr, "%d\t", i);
    state->digitalPin[STQ] = 1;
    state->digitalPin[Q1] = i & 0x01;
    state->digitalPin[Q2] = i & 0x02;
    state->digitalPin[Q3] = i & 0x04;
    state->digitalPin[Q4] = i & 0x08;
    assertEqual(i, DTMF.readRaw());
  }
}


unittest_main()

// --------
