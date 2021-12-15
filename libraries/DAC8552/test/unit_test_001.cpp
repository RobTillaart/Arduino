//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the DAC8552
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
#include "DAC8552.h"


unittest_setup()
{
  fprintf(stderr, "DAC8552_LIB_VERSION: %s\n", (char *) DAC8552_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0, DAC8552_POWERDOWN_NORMAL  );
  assertEqual(1, DAC8552_POWERDOWN_1K      );
  assertEqual(2, DAC8552_POWERDOWN_100K    );
  assertEqual(3, DAC8552_POWERDOWN_HIGH_IMP);
}


unittest(test_HW_constructor)
{
  DAC8552 mydac(10);
  mydac.begin();

  for (uint8_t channel = 0; channel < 2; channel++)
  {
    fprintf(stderr, "CHANNEL %d\n", channel);
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
  DAC8552 mydac(4, 5, 6);
  mydac.begin();
  
  for (uint8_t channel = 0; channel < 2; channel++)
  {
    fprintf(stderr, "CHANNEL %d\n", channel);
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
  DAC8552 mydac(4, 5, 6);
  mydac.begin();
  
  for (uint8_t channel = 0; channel < 2; channel++)
  {
    fprintf(stderr, "CHANNEL %d\n", channel);
    mydac.setPowerDown(channel, DAC8552_POWERDOWN_NORMAL);
    assertEqual(DAC8552_POWERDOWN_NORMAL, mydac.getPowerDownMode(channel));

    mydac.setPowerDown(channel, DAC8552_POWERDOWN_1K);
    assertEqual(DAC8552_POWERDOWN_1K, mydac.getPowerDownMode(channel));

    mydac.setPowerDown(channel, DAC8552_POWERDOWN_100K);
    assertEqual(DAC8552_POWERDOWN_100K, mydac.getPowerDownMode(channel));

    mydac.setPowerDown(channel, DAC8552_POWERDOWN_HIGH_IMP);
    assertEqual(DAC8552_POWERDOWN_HIGH_IMP, mydac.getPowerDownMode(channel));
  }
}


unittest_main()

// --------
