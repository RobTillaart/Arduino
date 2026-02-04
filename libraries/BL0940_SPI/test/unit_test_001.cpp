//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-12-29
// PURPOSE: unit tests for the BL0940_SPI library
//     URL: https://github.com/RobTillaart/BL0940_SPI
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
#include "BL0940_SPI.h"


unittest_setup()
{
  fprintf(stderr, "BL0940_SPI_LIB_VERSION: %s\n", (char *) BL0940_SPI_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(1, 1);
}


// unittest(test_constructor)
// {
  // BL0940_SPI obj;
// }


unittest_main()


//  -- END OF FILE --

