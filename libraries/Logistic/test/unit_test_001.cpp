//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-01-03
// PURPOSE: unit tests for the Logistic function
//          https://github.com/RobTillaart/Logistic
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
#include "Logistic.h"


unittest_setup()
{
    fprintf(stderr, "LOGISTIC_LIB_VERSION: %s\n", (char *) LOGISTIC_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  Logistic L;

  assertEqual(2.0, L.getRate());
}


unittest_main()


//  -- END OF FILE --
