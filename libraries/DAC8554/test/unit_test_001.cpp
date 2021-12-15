//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the DAC8554
//          https://github.com/RobTillaart/
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
#include "DAC8554.h"


unittest_setup()
{
  fprintf(stderr, "DAC8554_LIB_VERSION: %s\n", (char *) DAC8554_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0x00, DAC8554_POWERDOWN_NORMAL  );
  assertEqual(0x40, DAC8554_POWERDOWN_1K      );
  assertEqual(0x80, DAC8554_POWERDOWN_100K    );
  assertEqual(0xC0, DAC8554_POWERDOWN_HIGH_IMP);
}


unittest(test_HW_constructor)
{
  DAC8554 mydac(10);  // not used address parameter
  mydac.begin();

  for (uint8_t channel = 0; channel < 4; channel++)
  {
    fprintf(stderr, "Channel %d\t", channel);
    for (uint16_t val = 0; val < 65500; val += 30)
    {
      mydac.setValue(channel, val);
      if (mydac.getValue(channel) != val)
      {
        fprintf(stderr, "%d -> %d\n", val, mydac.getValue(channel));
      }
    }
    mydac.setValue(channel, 100);
    assertEqual(100, mydac.getValue(channel));
  }
}


unittest(test_SW_constructor)
{
  DAC8554 mydac(4, 5, 6);  // not used address parameter
  mydac.begin();
  
  for (uint8_t channel = 0; channel < 4; channel++)
  {
    fprintf(stderr, "Channel %d\t", channel);
    for (uint16_t val = 0; val < 65500; val += 30)
    {
      mydac.setValue(channel, val);
      if (mydac.getValue(channel) != val)
      {
        fprintf(stderr, "%d -> %d\n", val, mydac.getValue(channel));
      }
    }
    mydac.setValue(channel, 100);
    assertEqual(100, mydac.getValue(channel));
  }
}


unittest(test_powerDown)
{
  DAC8554 mydac(4, 5, 6);
  mydac.begin();

  for (uint8_t channel = 0; channel < 4; channel++)
  {
    fprintf(stderr, "Channel %d\n", channel);
    mydac.setPowerDown(channel, DAC8554_POWERDOWN_NORMAL);
    assertEqual(DAC8554_POWERDOWN_NORMAL, mydac.getPowerDownMode(channel));

    mydac.setPowerDown(channel, DAC8554_POWERDOWN_1K);
    assertEqual(DAC8554_POWERDOWN_1K, mydac.getPowerDownMode(channel));

    mydac.setPowerDown(channel, DAC8554_POWERDOWN_100K);
    assertEqual(DAC8554_POWERDOWN_100K, mydac.getPowerDownMode(channel));

    mydac.setPowerDown(channel, DAC8554_POWERDOWN_HIGH_IMP);
    assertEqual(DAC8554_POWERDOWN_HIGH_IMP, mydac.getPowerDownMode(channel));
  }
}


unittest_main()

// --------
