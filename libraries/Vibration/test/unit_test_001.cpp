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


unittest_main()


//  -- END OF FILE --

