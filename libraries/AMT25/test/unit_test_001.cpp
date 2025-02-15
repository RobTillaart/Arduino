//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-08
// PURPOSE: unit tests for the AMT25 rotary encoder
//          https://github.com/RobTillaart/AMT25
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
#include "AMT25.h"

// writing to a virtual device does not work
// as millis() function is not implemented in 
// the Arduino-CI environment


unittest_setup()
{
  fprintf(stderr, "AMT25_LIB_VERSION: %s\n", (char *) AMT25_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_base)
{
  AMT25 er(9);  //  HW SPI

  assertEqual(0, er.lastRead());
}


unittest_main()


//  -- END OF FILE --
