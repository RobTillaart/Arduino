//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-05-11
// PURPOSE: unit tests for the ShiftOutSlow library
//          https://github.com/RobTillaart/ShiftOutSlow
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
#include "ShiftOutSlow.h"


//  PATCH FOR DUE & ZERO FOR UNIT TEST - https://github.com/Arduino-CI/arduino_ci/issues/252
#if defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_SAMD)
//  - due         #  ARDUINO_ARCH_SAM    does not support shiftIn apparently
//  - zero        #  ARDUINO_ARCH_SAMD
#endif


unittest_setup()
{
  fprintf(stderr, "SHIFTOUTSLOW_LIB_VERSION:\t%s\n", (char *) SHIFTOUTSLOW_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  ShiftOutSlow SOS(12, 13);

  assertEqual(1, SOS.write(65));
  assertEqual(65, SOS.lastWritten());
  assertEqual(LSBFIRST, SOS.getBitOrder());

  SOS.setBitOrder(MSBFIRST);
  assertEqual(MSBFIRST, SOS.getBitOrder());

  SOS.setBitOrder();
  assertEqual(LSBFIRST, SOS.getBitOrder());
}


unittest(test_constructor_LSB)
{
  ShiftOutSlow SOS(12, 13, LSBFIRST);

  assertEqual(1, SOS.write(65));
  assertEqual(65, SOS.lastWritten());
  assertEqual(LSBFIRST, SOS.getBitOrder());

  SOS.setBitOrder(MSBFIRST);
  assertEqual(MSBFIRST, SOS.getBitOrder());
}


unittest(test_constructor_MSB)
{
  ShiftOutSlow SOS(12, 13, MSBFIRST);

  assertEqual(1, SOS.write(65));
  assertEqual(65, SOS.lastWritten());
  assertEqual(MSBFIRST, SOS.getBitOrder());

  SOS.setBitOrder(LSBFIRST);
  assertEqual(LSBFIRST, SOS.getBitOrder());
}


unittest(test_setDelay)
{
  ShiftOutSlow SOS(12, 13);

  for (uint16_t d = 0; d < 1000; d += 100)
  {
    SOS.setDelay(d);
    assertEqual(d, SOS.getDelay());
  }
  SOS.setDelay();
  assertEqual(0, SOS.getDelay());
}


unittest(test_print_interface)
{
  ShiftOutSlow SOS(12, 13);

  int x = SOS.print("hello world");
  assertEqual(11, x);

  int y = SOS.println("hello world");
  assertEqual(13, y);

  char str[20] = "hello world";
  // casting needed for CI environment.
  int z = SOS.write((const uint8_t*) str, 8);
  assertEqual(8, z);
}


unittest_main()


//  -- END OF FILE --

