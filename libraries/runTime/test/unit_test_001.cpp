//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-09-17
// PURPOSE: unit tests for the runTime library
//     URL: https://github.com/RobTillaart/runTime
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


#include "runTime.h"


unittest_setup()
{
  fprintf(stderr, "RUNTIME_LIB_VERSION: %s\n", (char *) RUNTIME_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(1, 1);
}


unittest(test_constructor)
{
  runTime rt;
  assertFalse(rt.isRunning());
  assertEqual(0, rt.seconds());
  assertEqual(0, rt.runCount());
  assertEqual(0, rt.averageSeconds());
}


unittest(test_start_stop)
{
  runTime rt;
  assertFalse(rt.isRunning());
  assertEqual(0, rt.seconds());
  assertEqual(0, rt.runCount());

  rt.start();
  assertTrue(rt.isRunning());
  assertEqual(0, rt.seconds());  //  unit test does no millis()
  assertEqual(1, rt.runCount());

  rt.stop();
  assertFalse(rt.isRunning());
  assertEqual(0, rt.seconds());
  assertEqual(1, rt.runCount());
}



unittest(test_start_reset)
{
  runTime rt;
  assertFalse(rt.isRunning());
  assertEqual(0, rt.seconds());
  assertEqual(0, rt.runCount());

  rt.start();
  assertTrue(rt.isRunning());
  assertEqual(0, rt.seconds());  //  unit test does no millis()
  assertEqual(1, rt.runCount());

  rt.reset();
  assertFalse(rt.isRunning());
  assertEqual(0, rt.seconds());
  assertEqual(0, rt.runCount());

  rt.reset(123);
  assertFalse(rt.isRunning());
  assertEqual(123, rt.seconds());
  assertEqual(0, rt.runCount());
}


unittest_main()


//  -- END OF FILE --

