//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-04-29
// PURPOSE: unit tests for the LTR390 library
//     URL: https://github.com/RobTillaart/LTR390
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

#include "LTR390.h"


unittest_setup()
{
  fprintf(stderr, "LTR390_LIB_VERSION: %s\n", (char *) LTR390_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  LTR390 dev;

  assertEqual(0x53, dev.getAddress());
}


unittest_main()


//  -- END OF FILE --

