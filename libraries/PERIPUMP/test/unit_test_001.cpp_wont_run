//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-10-13
// PURPOSE: unit tests for the peristaltic pump (DFR0523).
//          https://github.com/RobTillaart/peristaltic
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
#include "Servo.h"
#include "PERIPUMP.h"

#define pumpPin                 5


unittest_setup()
{
    fprintf(stderr, "PERIPUMP_LIB_VERSION: %s\n", (char *) PERIPUMP_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_percentage)
{
  PERIPUMP pump(5);

  pump.begin();
  assertEqual(0, pump.getPercentage(), 1);

  pump.stop();
  assertEqual(0, pump.getPercentage(), 1);

  for (int pos = -100; pos <= 100; pos += 10)
  {
    pump.setPercentage(pos);
    assertEqual(pos, pump.getPercentage(), 1);
  }

  pump.stop();
  assertEqual(0, pump.getPercentage(), 1);
}


unittest_main()


// -- END OF FILE --
