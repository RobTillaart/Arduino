//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-24
// PURPOSE: unit tests for the AD5370 library
//     URL: https://github.com/RobTillaart/AD5370
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
#include "AD5370.h"


unittest_setup()
{
  fprintf(stderr, "AD5370_LIB_VERSION: %s\n", (char *) AD5370_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  AD5370 dac40(6, 7, 8);

  for (uint32_t sp = 1000000; sp <= 8000000; sp += 1000000)
  {
    dac40.setSPIspeed(sp);
    assertEqual(dac40.getSPIspeed(), sp);
  }
}


unittest_main()


//  -- END OF FILE --

