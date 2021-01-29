//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the DAC8551
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
#include "DAC8551.h"


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_HW_constructor)
{
  DAC8551 DAC(10);
  DAC.begin();

  for (uint16_t val = 0; val < 65500; val += 30)
  {
    DAC.setValue(val);
    if (DAC.getValue() != val)
    {
      fprintf(stderr, "%d -> %d\n", val, DAC.getValue());
    }
  }
  DAC.setValue(100);
  assertEqual(100, DAC.getValue());
}


unittest(test_SW_constructor)
{
  DAC8551 DAC(4, 5, 6);
  DAC.begin();
  
  for (uint16_t val = 0; val < 65500; val += 30)
  {
    DAC.setValue(val);
    if (DAC.getValue() != val)
    {
      fprintf(stderr, "%d -> %d\n", val, DAC.getValue());
    }
  }
  DAC.setValue(100);
  assertEqual(100, DAC.getValue());
}


unittest(test_powerDown)
{
  DAC8551 DAC(4, 5, 6);
  DAC.begin();
  
  DAC.setPowerDown(DAC8551_POWERDOWN_NORMAL);
  assertEqual(DAC8551_POWERDOWN_NORMAL, DAC.getPowerDownMode());
  
  DAC.setPowerDown(DAC8551_POWERDOWN_1K);
  assertEqual(DAC8551_POWERDOWN_1K, DAC.getPowerDownMode());
  
  DAC.setPowerDown(DAC8551_POWERDOWN_100K);
  assertEqual(DAC8551_POWERDOWN_100K, DAC.getPowerDownMode());
  
  DAC.setPowerDown(DAC8551_POWERDOWN_HIGH_IMP);
  assertEqual(DAC8551_POWERDOWN_HIGH_IMP, DAC.getPowerDownMode());
}


unittest_main()

// --------
