//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-04-02
// PURPOSE: unit tests for the markDownWriter library
//     URL: https://github.com/RobTillaart/markDownWriter
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
#include "markDownWriter.h"


unittest_setup()
{
  fprintf(stderr, "MARKDOWNWRITER_LIB_VERSION: %s\n", (char *) MARKDOWNWRITER_LIB_VERSION);
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
  markDownWriter obj;
}


unittest_main()


//  -- END OF FILE --

