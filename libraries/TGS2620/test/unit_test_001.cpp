//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-10
// PURPOSE: unit tests for the TGS2620 library
//     URL: https://github.com/RobTillaart/TGS2620
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
#include "TGS2620.h"


unittest_setup()
{
  fprintf(stderr, "TGS2620_LIB_VERSION: %s\n", (char *) TGS2620_LIB_VERSION);
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
  TGS2620 obj(A0, 1023);
}


unittest_main()


//  -- END OF FILE --

