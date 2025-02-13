//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-12
// PURPOSE: unit tests for the I2C DAC53001
//          https://github.com/RobTillaart/DAC53001
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
#include "DAC53001.h"

// writing to a virtual device does not work
// as millis() function is not implemented in 
// the Arduino-CI environment


unittest_setup()
{
  fprintf(stderr, "DAC53001_LIB_VERSION: %s\n", (char *) DAC53001_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  DAC53001 dac0(0x30);
  DAC53002 dac1(0x31);
  DAC63001 dac2(0x32);
  DAC63002 dac3(0x33);

  assertEqual(48,   dac0.getAddress());
  assertEqual(1023, dac0.getMaxValue());
  assertEqual( 1,   dac0.getChannels());

  assertEqual(49,   dac1.getAddress());
  assertEqual(1023, dac1.getMaxValue());
  assertEqual( 2,   dac1.getChannels());

  assertEqual(50,   dac2.getAddress());
  assertEqual(4095, dac2.getMaxValue());
  assertEqual( 1,   dac2.getChannels());

  assertEqual(51,   dac3.getAddress());
  assertEqual(4095, dac3.getMaxValue());
  assertEqual( 2,   dac3.getChannels());
}


unittest_main()


//  -- END OF FILE --
