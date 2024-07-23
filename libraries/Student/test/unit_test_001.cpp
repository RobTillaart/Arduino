//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-07-22
// PURPOSE: unit tests for the Student library
//          https://github.com/RobTillaart/Student
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
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


#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "Student.h"


unittest_setup()
{
    fprintf(stderr, "STUDENT_LIB_VERSION: %s\n", (char *) STUDENT_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(20, STUDENT_MAX_SIZE);
}


unittest(test_constructor)
{
  Student S;

  assertEqual(20, S.getSize());
  assertEqual(00, S.getCount());
}


unittest(test_all)
{
  Student S;

  S.reset();
  assertEqual(0, S.getCount());

  S.add(12.4);
  S.add(11.8);
  S.add(12.0);
  S.add(11.7);
  S.add(12.1);
  S.add(12.3);
  S.add(11.9);
  S.add(11.6);
  S.add(11.9);
  S.add(12.3);

  assertEqual(10, S.getCount());
  assertEqualFloat(12.0, S.mean(), 0.001);
  assertEqualFloat(0.073, S.variance(), 0.001);
  assertEqualFloat(0.271, S.deviation(), 0.001);
  assertEqualFloat(0.086, S.estimatedDeviation(), 0.001);

  assertEqualFloat(11.809, S.meanLower(95), 0.001);
  assertEqualFloat(12.191, S.meanUpper(95), 0.001);
}


unittest_main()


//  -- END OF FILE --

