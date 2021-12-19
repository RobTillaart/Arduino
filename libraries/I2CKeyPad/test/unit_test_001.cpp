//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-27
// PURPOSE: unit tests for the I2CKeyPad library
//          https://github.com/RobTillaart/I2CKeyPad
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
#include "I2CKeyPad.h"


unittest_setup()
{
  fprintf(stderr, "I2C_KEYPAD_LIB_VERSION: %s\n", (char *) I2C_KEYPAD_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(16, I2C_KEYPAD_NOKEY);
  assertEqual(17, I2C_KEYPAD_FAIL);
}



unittest(test_constructor)
{
  const uint8_t KEYPAD_ADDRESS = 0x38;
  I2CKeyPad keyPad(KEYPAD_ADDRESS);

  assertEqual(I2C_KEYPAD_NOKEY, keyPad.getLastKey());

  // assertTrue(keyPad.begin());
  // assertTrue(keyPad.isConnected());
}


// Issues with Wire - to be investigated...
//
// unittest(test_read)
// {
  // const uint8_t KEYPAD_ADDRESS = 0x38;
  // I2CKeyPad keyPad(KEYPAD_ADDRESS);

  // assertTrue(keyPad.isConnected());
  // // assertTrue(keyPad.begin());

  // // assertEqual(I2C_KEYPAD_NOKEY, keyPad.getKey());
  // // assertFalse(keyPad.isPressed());
// }


unittest_main()

// --------
