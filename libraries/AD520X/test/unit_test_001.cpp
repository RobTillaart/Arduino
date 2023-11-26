//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2020-12-08
// PURPOSE: unit tests for the AD520X digital potentiometers
//          https://github.com/RobTillaart/AD520X
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
#include "AD520X.h"


unittest_setup()
{
}


unittest_teardown()
{
}


unittest(test_begin)
{
  fprintf(stderr, "AD520X_LIB_VERSION:\t%s\n", (char *) AD520X_LIB_VERSION);
  AD5204 pot = AD5204(10, 12, 13);  //  HW SPI by default
  pot.begin();
  assertEqual(128, pot.getValue(0));

  pot.begin(42);
  assertEqual(42, pot.getValue(0));
}


unittest(test_setValue)
{
  AD5206 pot = AD5206(10, 12, 13);  //  HW SPI by default
  pot.begin();
  assertEqual(128, pot.getValue(0));

  for (int i = 0; i < pot.pmCount(); i++)
  {
    pot.setValue(i, 35);
    assertEqual(35, pot.getValue(i));
  }

  pot.setAll(42);
  for (int i = 0; i < pot.pmCount(); i++)
  {
    assertEqual(42, pot.getValue(i));
  }

  pot.setAll();
  for (int i = 0; i < pot.pmCount(); i++)
  {
    assertEqual(128, pot.getValue(i));
  }

  assertFalse(pot.setValue(6, 10));

  AD8400 p8400 = AD8400(10, 12, 13);
  assertFalse(p8400.setValue(1, 117));
}


unittest(test_setPercentage)
{
  AD5206 pot = AD5206(10, 12, 13, 7, 6);  //  SW SPI
  pot.begin();
  assertEqualFloat(50, pot.getPercentage(0), 0.5);

  for (int i = 0; i < pot.pmCount(); i++)
  {
    pot.setPercentage(i, 35);
    assertEqualFloat(35, pot.getPercentage(i), 0.5);
  }
}


unittest(test_reset)
{
  AD5204 pot = AD5204(10, 12, 13);  //  HW SPI by default
  pot.begin();
  assertEqual(128, pot.getValue(0));
  
  pot.reset(35);
  for (int i = 0; i < pot.pmCount(); i++)
  {
    assertEqual(35, pot.getValue(i));
  }
}


unittest(test_power)
{
  AD5204 pot = AD5204(10, 12, 13);  //  HW SPI by default
  pot.begin(213);
  assertEqual(213, pot.getValue(0));
  assertTrue(pot.isPowerOn());

  pot.powerOff();
  assertFalse(pot.isPowerOn());
  delay(100);

  pot.powerOn();
  assertTrue(pot.isPowerOn());
  delay(100);

  for (int i = 0; i < pot.pmCount(); i++)
  {
    assertEqual(213, pot.getValue(i));
  }
}


unittest(test_pm_count_HARDWARE_SPI)
{
  AD5204 pot1 = AD5204(10, 12, 13);  //  HW SPI by default
  pot1.begin();
  assertEqual(4, pot1.pmCount());

  AD5206 pot2 = AD5206(10, 12, 13);
  pot2.begin();
  assertEqual(6, pot2.pmCount());

  AD8403 pot3 = AD8403(10, 12, 13);
  pot3.begin();
  assertEqual(4, pot3.pmCount());

  AD8402 pot4 = AD8402(10, 12, 13);
  pot4.begin();
  assertEqual(2, pot4.pmCount());

  AD8400 pot5 = AD8400(10, 12, 13);
  pot5.begin();
  assertEqual(1, pot5.pmCount());
}


unittest(test_pm_count_SOFTWARE_SPI)
{
  AD5204 pot1 = AD5204(10, 12, 13, 6, 7);
  pot1.begin();
  assertEqual(4, pot1.pmCount());

  AD5206 pot2 = AD5206(10, 12, 13, 6, 7);
  pot2.begin();
  assertEqual(6, pot2.pmCount());

  AD8403 pot3 = AD8403(10, 12, 13, 6, 7);
  pot3.begin();
  assertEqual(4, pot3.pmCount());

  AD8402 pot4 = AD8402(10, 12, 13, 6, 7);
  pot4.begin();
  assertEqual(2, pot4.pmCount());

  AD8400 pot5 = AD8400(10, 12, 13, 6, 7);
  pot5.begin();
  assertEqual(1, pot5.pmCount());
}


unittest_main()

//  -- END OF FILE --
