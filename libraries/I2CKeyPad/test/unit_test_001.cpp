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
  assertEqual(255, I2C_KEYPAD_THRESHOLD);

  assertEqual(44, I2C_KEYPAD_4x4);
  assertEqual(53, I2C_KEYPAD_5x3);
  assertEqual(62, I2C_KEYPAD_6x2);
  assertEqual(81, I2C_KEYPAD_8x1);
}



unittest(test_constructor)
{
  const uint8_t KEYPAD_ADDRESS = 0x38;
  I2CKeyPad keyPad(KEYPAD_ADDRESS);

  assertEqual(I2C_KEYPAD_NOKEY, keyPad.getLastKey());

  // assertTrue(keyPad.begin());
  // assertTrue(keyPad.isConnected());
}


unittest(test_mode)
{
  const uint8_t KEYPAD_ADDRESS = 0x38;
  I2CKeyPad keyPad(KEYPAD_ADDRESS);

  assertEqual(I2C_KEYPAD_4x4, keyPad.getKeyPadMode());

  keyPad.setKeyPadMode(I2C_KEYPAD_5x3);
  assertEqual(I2C_KEYPAD_5x3, keyPad.getKeyPadMode());

  keyPad.setKeyPadMode(I2C_KEYPAD_4x4);
  assertEqual(I2C_KEYPAD_4x4, keyPad.getKeyPadMode());

  keyPad.setKeyPadMode(I2C_KEYPAD_6x2);
  assertEqual(I2C_KEYPAD_6x2, keyPad.getKeyPadMode());

  keyPad.setKeyPadMode(I2C_KEYPAD_8x1);
  assertEqual(I2C_KEYPAD_8x1, keyPad.getKeyPadMode());

  //  invalid are mapped to 4x4
  keyPad.setKeyPadMode(00);
  assertEqual(I2C_KEYPAD_4x4, keyPad.getKeyPadMode());
}


unittest(test_KeyMap)
{
  const uint8_t KEYPAD_ADDRESS = 0x38;
  I2CKeyPad keyPad(KEYPAD_ADDRESS);

  char keymap[19] = "123A456B789C*0#DNF";
  keyPad.loadKeyMap(keymap);
  assertEqual('N', keyPad.getLastChar());
}


unittest(test_debounce_threshold)
{
  const uint8_t KEYPAD_ADDRESS = 0x38;
  I2CKeyPad keyPad(KEYPAD_ADDRESS);

  //  default 0
  assertEqual(0, keyPad.getDebounceThreshold());

  for (uint16_t th = 5000; th < 60000; th += 5000)
  {
    keyPad.setDebounceThreshold(th);
    assertEqual(th, keyPad.getDebounceThreshold());
  }
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
