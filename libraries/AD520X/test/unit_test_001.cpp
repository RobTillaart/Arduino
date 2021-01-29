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
  AD5204 pot = AD5204(10, 12, 13);  // HW SPI
  pot.begin();
  assertEqual(128, pot.getValue(0));

  pot.begin(42);
  assertEqual(42, pot.getValue(0));
}

unittest(test_setValue)
{
  AD5206 pot = AD5206(10, 12, 13);  // HW SPI
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
}


unittest(test_reset)
{
  AD5204 pot = AD5204(10, 12, 13);  // HW SPI
  pot.begin();
  assertEqual(128, pot.getValue(0));
  
  pot.reset(35);
  assertEqual(35, pot.getValue(0));
}


unittest(test_power)
{
  AD5204 pot = AD5204(10, 12, 13);  // HW SPI
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


unittest(test_pm_count)
{
  AD5204 pot1 = AD5204(10, 12, 13);  // HW SPI
  pot1.begin();
  assertEqual(4, pot1.pmCount());

  AD5206 pot2 = AD5206(10, 12, 13);  // HW SPI
  pot2.begin();
  assertEqual(6, pot2.pmCount());

  AD8403 pot3 = AD8403(10, 12, 13);  // HW SPI
  pot3.begin();
  assertEqual(4, pot3.pmCount());

  AD8402 pot4 = AD8402(10, 12, 13);  // HW SPI
  pot4.begin();
  assertEqual(2, pot4.pmCount());

  AD8400 pot5 = AD8400(10, 12, 13);  // HW SPI
  pot5.begin();
  assertEqual(1, pot5.pmCount());
}


unittest_main()

// --------
