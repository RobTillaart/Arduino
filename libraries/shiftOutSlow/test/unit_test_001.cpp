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


// PATCH FOR DUE & ZERO FOR UNIT TEST - https://github.com/Arduino-CI/arduino_ci/issues/252
#if defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_SAMD)
// - due         #  ARDUINO_ARCH_SAM    does not support shiftIn apparently
// - zero        #  ARDUINO_ARCH_SAMD   
#endif


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  ShiftOutSlow SOS(12, 13);

  fprintf(stderr, "VERSION:\t%s\n", SHIFTOUTSLOW_LIB_VERSION);
  assertEqual(1, SOS.write(65));
  assertEqual(65, SOS.lastWritten());
  assertEqual(LSBFIRST, SOS.getBitOrder());
  
  SOS.setBitOrder(MSBFIRST);
  assertEqual(MSBFIRST, SOS.getBitOrder());
}


unittest(test_constructor_LSB)
{
  ShiftOutSlow SOS(12, 13, LSBFIRST);

  fprintf(stderr, "VERSION:\t%s\n", SHIFTOUTSLOW_LIB_VERSION);
  assertEqual(1, SOS.write(65));
  assertEqual(65, SOS.lastWritten());
  assertEqual(LSBFIRST, SOS.getBitOrder());
  
  SOS.setBitOrder(MSBFIRST);
  assertEqual(MSBFIRST, SOS.getBitOrder());
}


unittest(test_constructor_MSB)
{
  ShiftOutSlow SOS(12, 13, MSBFIRST);

  fprintf(stderr, "VERSION:\t%s\n", SHIFTOUTSLOW_LIB_VERSION);
  assertEqual(1, SOS.write(65));
  assertEqual(65, SOS.lastWritten());
  assertEqual(MSBFIRST, SOS.getBitOrder());
  
  SOS.setBitOrder(LSBFIRST);
  assertEqual(LSBFIRST, SOS.getBitOrder());
}


unittest(test_setDelay)
{
  ShiftOutSlow SOS(12, 13);

  fprintf(stderr, "VERSION:\t%s\n", SHIFTOUTSLOW_LIB_VERSION);
  for (uint16_t d = 0; d < 1000; d += 100)
  {
    SOS.setDelay(d);
    assertEqual(d, SOS.getDelay());
  }
}

unittest_main()

// --------
