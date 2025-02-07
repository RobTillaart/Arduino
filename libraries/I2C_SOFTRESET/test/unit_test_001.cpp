//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-03
// PURPOSE: unit tests for the Arduino library for the I2C_SOFTRESET
//          https://github.com/RobTillaart/I2C_SOFTRESET
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
#include "I2C_SoftReset.h"



unittest_setup()
{
  fprintf(stderr, "I2C_SOFTRESET_LIB_VERSION: %s\n", (char *) I2C_SOFTRESET_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(constructors)
{
  I2C_SOFTRESET I2CBUS(A4, A5);

  assertEqual(0, I2CBUS.lastReset());
  I2CBUS.reset();
}




unittest_main()


//  -- END OF FILE --
