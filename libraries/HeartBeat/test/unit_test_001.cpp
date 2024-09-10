//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the HeartBeat
//          https://github.com/RobTillaart/HeartBeat
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
#include "HeartBeat.h"


unittest_setup()
{
  fprintf(stderr, "HEARTBEAT_LIB_VERSION: %s\n", (char *) HEARTBEAT_LIB_VERSION );
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  GodmodeState* state = GODMODE();
  state->reset();

  HeartBeat HB;
  HB.begin(13, 4);

  uint32_t start = millis();
  while (millis() - start <= 1000)
  {
    delay(10);
    HB.beat();
  }
  
  assertEqual(0, state->digitalPin[13].queueSize());
  bool expected[8] = {LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW, HIGH};
  bool actual[8];
  int  changes = state->digitalPin[13].toArray(actual, 8);
  assertEqual(8, changes);

  // verify each element
  for (int i = 0; i < 8; ++i) 
  {
    fprintf(stderr, "%d\t", i);
    assertEqual(expected[i], actual[i]);
  }
}


unittest(test_frequency)
{
  HeartBeat HB;
  HB.begin(13, 4);
  
  assertEqualFloat(4, HB.getFrequency(), 0.001);
  for (int fr = 1; fr < 10; fr++)
  {
    HB.setFrequency(fr);
    assertEqualFloat(fr, HB.getFrequency(), 0.001);
  }
}


unittest(test_dutycycle)
{
  HeartBeat HB;
  HB.begin(13, 1);

  for (int dc = 10; dc < 101; dc += 10)
  {
    HB.setDutyCycle(dc);
    assertEqualFloat(dc, HB.getDutyCycle(), 0.001);
  }
}


unittest(test_HBDIAG)
{
  HeartBeatDiag HBD;
  HBD.begin(13, 1);

  //  verify default value
  assertTrue(HBD.codeCompleted());
}


unittest(test_HBSL)
{
  HeartBeatSL HBD;
  HBD.begin(13, 1);

  //  verify default value
  assertTrue(HBD.codeCompleted());
}


unittest_main()


//  -- END OF FILE --

