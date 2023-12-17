//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-12-17
// PURPOSE: unit tests for the I2C_LCD 
//          https://github.com/RobTillaart/I2C_LCD
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
#include "I2C_LCD.h"


unittest_setup()
{
  fprintf(stderr, "I2C_LCD_LIB_VERSION: %s\n", (char *) I2C_LCD_LIB_VERSION);
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
  I2C_LCD lcd(0x39);

  assertEqual(1, 1);
}



unittest_main()


//  -- END OF FILE --


