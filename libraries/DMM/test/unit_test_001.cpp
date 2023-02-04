//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-12-19
// PURPOSE: unit tests for DMM class
//          https://github.com/RobTillaart/DMM
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

#ifndef A0
#define A0  14
#endif

#include "DMM.h"


unittest_setup()
{
    fprintf(stderr, "DMM_LIB_VERSION: %s\n", (char *) DMM_LIB_VERSION);
}


unittest_teardown()
{
}


//  placeholder for now

unittest(test_first)
{
  DMM dmm;
  assertEqual(1,1);
}


unittest_main()


//  -- END OF FILE --
