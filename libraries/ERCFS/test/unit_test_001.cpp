//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-08
// PURPOSE: unit tests for the ERCFS rotary encoder
//          https://github.com/RobTillaart/ERCFS
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
#include "ERCFS.h"

// writing to a virtual device does not work
// as millis() function is not implemented in 
// the Arduino-CI environment


unittest_setup()
{
  fprintf(stderr, "ERCFS_LIB_VERSION: %s\n", (char *) ERCFS_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_base)
{
  ERCFS er(9);  //  HW SPI

  assertEqual(0, er.lastRead());
}


unittest_main()


//  -- END OF FILE --
