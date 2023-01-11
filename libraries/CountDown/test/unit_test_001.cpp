//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the CountDown Library
//          https://github.com/RobTillaart/CountDown
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)
// assertNotNull(actual)


#include <ArduinoUnitTests.h>


#include "Arduino.h"
#include "CountDown.h"



unittest_setup()
{
  fprintf(stderr, "COUNTDOWN_LIB_VERSION: %s\n", (char *) COUNTDOWN_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual('M', CountDown::MINUTES);
  assertEqual('s', CountDown::SECONDS);
  assertEqual('m', CountDown::MILLIS);
  assertEqual('u', CountDown::MICROS);
}


unittest(test_constructor)
{
  CountDown a(CountDown::MINUTES);
  CountDown b(CountDown::SECONDS);
  CountDown c(CountDown::MILLIS);
  CountDown d(CountDown::MICROS);
  CountDown e;  // default MILLIS

  assertEqual(CountDown::MINUTES, a.resolution());
  assertEqual(CountDown::SECONDS, b.resolution());
  assertEqual(CountDown::MILLIS,  c.resolution());
  assertEqual(CountDown::MICROS,  d.resolution());
  assertEqual(CountDown::MILLIS,  e.resolution());

  assertEqual('M', a.getUnits());
  assertEqual('s', b.getUnits());
  assertEqual('m',  c.getUnits());
  assertEqual('u',  d.getUnits());
  assertEqual('m',  e.getUnits());

  fprintf(stderr, "\nisRunning\n");

  assertFalse(a.isRunning());
  assertFalse(b.isRunning());
  assertFalse(c.isRunning());
  assertFalse(d.isRunning());
  assertFalse(e.isRunning());

  fprintf(stderr, "\nbase\n");
  
  a.setResolution(CountDown::SECONDS);
  assertTrue(a.start(10));
  assertTrue(a.isRunning());

  a.stop();
  assertFalse(a.isRunning());

  a.cont();
  assertTrue(a.isRunning());

  a.stop();
  assertFalse(a.isRunning());

  assertTrue(a.start(0));
  assertFalse(a.isRunning());
}


unittest(test_run)
{
  CountDown cd(CountDown::MILLIS);
  assertEqual(CountDown::MILLIS,  cd.resolution());

  assertFalse(cd.isRunning());
  assertTrue(cd.isStopped());
  cd.start(10);
  assertTrue(cd.isRunning());
  assertFalse(cd.isStopped());
  delay(5);
  cd.stop();
  assertFalse(cd.isRunning());
  assertTrue(cd.isStopped());
  assertEqual(5, cd.remaining());

  cd.start(10);
  assertTrue(cd.isRunning());
  assertFalse(cd.isStopped());
  delay(15);
  assertFalse(cd.isRunning());
  assertTrue(cd.isStopped());
  assertEqual(0, cd.remaining());
}


unittest(test_overflow)
{
  CountDown cd;
  assertEqual(CountDown::MILLIS, cd.resolution());

  assertFalse(cd.isRunning());
  assertFalse(cd.start(50, 0, 0));
  assertEqual(CountDown::MINUTES, cd.resolution());

  assertFalse(cd.start(50, 0, 0, 0));
  assertEqual(CountDown::SECONDS, cd.resolution());

  assertFalse(cd.start(0, 1200, 0));
  assertFalse(cd.start(0, 1200, 0, 0));

  assertFalse(cd.start(0, 0, 72000));
  assertFalse(cd.start(0, 0, 72000, 0));

  assertFalse(cd.start(0, 0, 0, 4320000));
}


unittest_main()


//  -- END OF FILE --

