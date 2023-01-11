//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-08
// PURPOSE: unit tests for the StopWatch library
//          https://github.com/RobTillaart/StopWatch_RT
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
#include "StopWatch.h"


unittest_setup()
{
  fprintf(stderr, "STOPWATCH_LIB_VERSION: %s\n", (char *) STOPWATCH_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants_dividers)
{
  assertEqual(STOPWATCH_SECONDS_DIVIDER,  1000);
  assertEqual(STOPWATCH_MINUTES_DIVIDER,  60000);
}


unittest(test_constants_units)
{
  assertEqual('u',  StopWatch::MICROS);
  assertEqual('m',  StopWatch::MILLIS);
  assertEqual('s',  StopWatch::SECONDS);
  assertEqual('M',  StopWatch::MINUTES);
}



unittest(test_constructor)
{
  StopWatch stopwatch0;

  assertFalse(stopwatch0.isRunning());
  assertEqual(StopWatch::RESET, stopwatch0.state());
  assertEqual(StopWatch::MILLIS, stopwatch0.resolution());

  StopWatch stopwatch1(StopWatch::MICROS);
  assertEqual(StopWatch::MICROS, stopwatch1.resolution());

  StopWatch stopwatch2(StopWatch::SECONDS);
  assertEqual(StopWatch::SECONDS, stopwatch2.resolution());

  StopWatch stopwatch3(StopWatch::MINUTES);
  assertEqual(StopWatch::MINUTES, stopwatch3.resolution());
}


unittest(test_run)
{
  StopWatch stopwatch;

  assertFalse(stopwatch.isRunning());
  assertFalse(stopwatch.isStopped());
  assertTrue(stopwatch.isReset());

  stopwatch.start();
  delay(101);
  assertTrue(stopwatch.isRunning());
  assertFalse(stopwatch.isStopped());
  assertFalse(stopwatch.isReset());
  assertEqual(StopWatch::RUNNING, stopwatch.state());
  assertLessOrEqual(100, stopwatch.elapsed());

  stopwatch.stop();
  assertFalse(stopwatch.isRunning());
  assertTrue(stopwatch.isStopped());
  assertFalse(stopwatch.isReset());
  assertEqual(StopWatch::STOPPED, stopwatch.state());

  uint32_t ti = stopwatch.elapsed();
  stopwatch.start();
  delay(10);
  assertTrue(stopwatch.isRunning());
  assertFalse(stopwatch.isStopped());
  assertFalse(stopwatch.isReset());
  assertLessOrEqual(110, stopwatch.elapsed());

  stopwatch.reset();
  assertFalse(stopwatch.isRunning());
  assertFalse(stopwatch.isStopped());
  assertTrue(stopwatch.isReset());
  assertEqual(StopWatch::RESET, stopwatch.state());
}


unittest(test_resolution)
{
  StopWatch stopwatch;

  stopwatch.setResolution(StopWatch::MICROS);
  assertEqual(StopWatch::MICROS, stopwatch.resolution());

  stopwatch.setResolution(StopWatch::MILLIS);
  assertEqual(StopWatch::MILLIS, stopwatch.resolution());

  stopwatch.setResolution(StopWatch::SECONDS);
  assertEqual(StopWatch::SECONDS, stopwatch.resolution());

  stopwatch.setResolution(StopWatch::MINUTES);
  assertEqual(StopWatch::MINUTES, stopwatch.resolution());
}


unittest_main()

// --------
