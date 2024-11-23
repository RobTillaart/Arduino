//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2024-11-22
// PURPOSE: unit tests for the AD523X digital potentiometers
//          https://github.com/RobTillaart/AD523X
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
#include "AD523X.h"


unittest_setup()
{
  fprintf(stderr, "AD523X_LIB_VERSION:\t%s\n", (char *) AD523X_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual( 512, AD523X_MIDDLE_VALUE);
  assertEqual(1023, AD523X_MAX_VALUE);
}


unittest(test_begin)
{
  AD5231 pot = AD5231(10, 12);  //  HW SPI by default
  pot.begin();
  assertEqual(512, pot.getValue(0));

  pot.begin(42);
  assertEqual(42, pot.getValue(0));
}


unittest(test_setValue)
{
  AD5235 pot = AD5235(10, 12);  //  HW SPI by default
  pot.begin();
  assertEqual(512, pot.getValue(0));

  for (int pm = 0; pm < pot.pmCount(); pm++)
  {
    pot.setValue(pm, 935);
    assertEqual(935, pot.getValue(pm));
  }

  pot.setAll(542);
  for (int pm = 0; pm < pot.pmCount(); pm++)
  {
    assertEqual(542, pot.getValue(pm));
  }

  //  pm out of range
  assertFalse(pot.setValue(3, 10));
}


unittest(test_setPercentage)
{
  AD5235 pot = AD5235(10, 12, 13, 7, 6);  //  SW SPI
  pot.begin();
  assertEqualFloat(50, pot.getPercentage(0), 0.5);

  for (int pm = 0; pm < pot.pmCount(); pm++)
  {
    pot.setPercentage(pm, 35.3);
    assertEqualFloat(35.3, pot.getPercentage(pm), 0.1);
  }

  pot.setPercentageAll(66.7);
  for (int pm = 0; pm < pot.pmCount(); pm++)
  {
    assertEqualFloat(66.7, pot.getPercentage(pm), 0.1);
  }
}


unittest(test_reset)
{
  AD5235 pot = AD5235(10, 12);  //  HW SPI by default
  pot.begin();
  assertEqual(512, pot.getValue(0));

  pot.reset(35);
  for (int i = 0; i < pot.pmCount(); i++)
  {
    assertEqual(35, pot.getValue(i));
  }
}


unittest(test_pm_count_HARDWARE_SPI)
{
  AD5231 pot1 = AD5231(10, 12);  //  HW SPI by default
  pot1.begin();
  assertEqual(1, pot1.pmCount());

  AD5235 pot2 = AD5235(10, 12);
  pot2.begin();
  assertEqual(2, pot2.pmCount());
}


unittest(test_pm_count_SOFTWARE_SPI)
{
  AD5231 pot1 = AD5231(10, 12, 13, 6, 7);  //  SW SPI
  pot1.begin();
  assertEqual(1, pot1.pmCount());

  AD5235 pot2 = AD5235(10, 12, 13, 6, 7);  //  SW SPI
  pot2.begin();
  assertEqual(2, pot2.pmCount());
}


unittest_main()


//  -- END OF FILE --

