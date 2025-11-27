//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-10-01
// PURPOSE: unit tests for the Vibration library
//     URL: https://github.com/RobTillaart/Vibration
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
#include "Vibration.h"


unittest_setup()
{
  fprintf(stderr, "VIBRATION_LIB_VERSION: %s\n", (char *) VIBRATION_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  VibrationSensor vib(A2);

  assertTrue(vib.begin());
}


unittest(test_noiseLevel)
{
  VibrationSensor vib(A2);

  //  default value
  assertEqual(10, vib.getNoiseLevel());

  //  setting different values
  for (int i = 0; i < 20; i+=2)
  {
    vib.setNoiseLevel(i);
    assertEqual(i, vib.getNoiseLevel());
  }

  //  default parameter
  vib.setNoiseLevel();
  assertEqual(10, vib.getNoiseLevel());
}


unittest(test_defaults)
{
  VibrationSensor vib(A2);

  //  raw data.
  assertEqual(10, vib.getNoiseLevel());
  assertEqual(0, vib.sampleCount());
  assertEqual(0, vib.maxValue());
  assertEqual(0, vib.sum());

  //  divide by zero.
  assertNAN(vib.zeroCount());
  assertNAN(vib.average());
}


unittest_main()


//  -- END OF FILE --

