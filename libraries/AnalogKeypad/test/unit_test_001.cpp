//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the AnalogKeypad library
//          https://github.com/RobTillaart/AnalogKeypad
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
#include "AnalogKeypad.h"


unittest_setup()
{
  fprintf(stderr, "ANALOGKEYPAD_LIB_VERSION: %s\n", (char *) ANALOGKEYPAD_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0x00, NOKEY   );
  assertEqual(0x80, PRESSED );
  assertEqual(0x40, RELEASED);
  assertEqual(0x20, REPEATED);
  assertEqual(0x10, CHANGED );
}


unittest(test_constructor)
{
  AnalogKeypad AKP(0);
  int press = AKP.pressed();
  assertEqual(0, press);
}


unittest(test_polling)
{
  AnalogKeypad AKP(0);
  int key = AKP.read();
  assertEqual(0, key);
}


unittest(test_event)
{
  AnalogKeypad AKP(0);
  int event = AKP.event();
  assertEqual(0, event);

  int key = AKP.key();
  assertEqual(0, key);
}


unittest_main()


//  -- END OF FILE --

