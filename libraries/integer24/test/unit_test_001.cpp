//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-06-22
// PURPOSE: unit tests for the integer24 datatype
//          https://github.com/RobTillaart/integer24
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
//  #include "integer24.h"


unittest_setup()
{
  // fprintf(stderr, "INTEGER24_LIB_VERSION: %s\n", (char *) INTEGER24_LIB_VERSION);
  fprintf(stderr, "Arduino CI does not support __uint24 for AVR\n");
  fprintf(stderr, "Tests are done in the examples.\n");
}


unittest_teardown()
{
}


unittest_main()


//  -- END OF FILE --
