//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-10-29
// PURPOSE: unit test-s for the Arduino software SPI library
//          https://github.com/RobTillaart/SWSPI
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
#include "SWSPI.h"



unittest_setup()
{
    fprintf(stderr, "SWSPI_LIB_VERSION: %s\n", (char *) SWSPI_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  SWSPI myspi(8,9,10);

  assertEqual(1, 1);
  //  TODO
}


unittest_main()


//  -- END OF FILE --
