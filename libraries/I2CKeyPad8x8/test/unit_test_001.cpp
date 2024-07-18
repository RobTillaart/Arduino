//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-09-28
// PURPOSE: unit tests for the I2CKeyPad8x8 library
//          https://github.com/RobTillaart/I2CKeyPad8x8
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
#include "I2CKeyPad8x8.h"


unittest_setup()
{
  fprintf(stderr, "I2C_KEYPAD8x8_LIB_VERSION: %s\n", (char *) I2C_KEYPAD8x8_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(64, I2C_KEYPAD8x8_NOKEY);
  assertEqual(65, I2C_KEYPAD8x8_FAIL);
  assertEqual(255, I2C_KEYPAD8x8_THRESHOLD);
}



unittest(test_constructor)
{
  const uint8_t KEYPAD_ADDRESS = 0x38;
  I2CKeyPad8x8 keyPad(KEYPAD_ADDRESS);

  assertEqual(I2C_KEYPAD8x8_NOKEY, keyPad.getLastKey());

  // assertTrue(keyPad.begin());
  // assertTrue(keyPad.isConnected());
}


unittest(test_debounce_threshold)
{
  const uint8_t KEYPAD_ADDRESS = 0x38;
  I2CKeyPad8x8 keyPad(KEYPAD_ADDRESS);

  //  default 0
  assertEqual(0, keyPad.getDebounceThreshold());

  for (uint16_t th = 5000; th < 60000; th += 5000)
  {
    keyPad.setDebounceThreshold(th);
    assertEqual(th, keyPad.getDebounceThreshold());
  }
}


// unittest(test_KeyMap)
// {
  // const uint8_t KEYPAD_ADDRESS = 0x38;
  // I2CKeyPad8x8 keyPad(KEYPAD_ADDRESS);

  // char keymap[66] = "123A456B789C*0#DNF";
  // keyPad.loadKeyMap(keymap);
  // assertEqual('N', keyPad.getLastChar());
// }


// Issues with Wire - to be investigated...
//
// unittest(test_read)
// {
  // const uint8_t KEYPAD_ADDRESS = 0x38;
  // I2CKeyPad8x8 keyPad(KEYPAD_ADDRESS);

  // assertTrue(keyPad.isConnected());
  // // assertTrue(keyPad.begin());

  // // assertEqual(I2C_KEYPAD_NOKEY, keyPad.getKey());
  // // assertFalse(keyPad.isPressed());
// }


unittest_main()

// --------
