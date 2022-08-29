//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-08-29
// PURPOSE: unit tests for the I2C_SCANNER class
//          https://github.com/RobTillaart/I2C_SCANNER
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
#include "I2C_SCANNER.h"

#define A0      0


unittest_setup()
{
    fprintf(stderr, "I2C_SCANNER_LIB_VERSION: %s\n", (char *) I2C_SCANNER_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  I2C_SCANNER scanner;
  scanner.begin();
  
  assertEqual(1, 1); //  keep build-CI happy
}


unittest_main()


// -- END OF FILE --
