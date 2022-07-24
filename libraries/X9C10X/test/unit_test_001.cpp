//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-02-11
// PURPOSE: unit tests for the X9C10X library
//          https://github.com/RobTillaart/X9C10X
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
#include "X9C10X.h"


unittest_setup()
{
  fprintf(stderr, "X9C10X_LIB_VERSION: %s\n", (char *) X9C10X_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_X9C_all)
{
  X9C pot;
  pot.begin(4,5,6);
  assertTrue(pot.incr());
  assertTrue(pot.decr());
  //  store() cannot be tested as it calls delay().
}


unittest(test_X9C10X_constructor)
{
  X9C10X dp0;
  X9C10X dp1(1000);
  X9C10X dp2(900);
  X9C10X dp3(1100);

  assertEqual(10000, dp0.getMaxOhm());
  assertEqual(1000,  dp1.getMaxOhm());
  assertEqual(900,   dp2.getMaxOhm());
  assertEqual(1100,  dp3.getMaxOhm());

  X9C10X x10x;
  X9C102 x102;
  X9C103 x103;
  X9C104 x104;
  X9C503 x503;

  assertEqual(10000,  x10x.getMaxOhm());
  assertEqual(1000,   x102.getMaxOhm());
  assertEqual(10000,  x103.getMaxOhm());
  assertEqual(100000, x104.getMaxOhm());
  assertEqual(50000,  x503.getMaxOhm());

  assertEqual(000, x10x.getType());
  assertEqual(102, x102.getType());
  assertEqual(103, x103.getType());
  assertEqual(104, x104.getType());
  assertEqual(503, x503.getType());
}


unittest(test_X9C10X_restore_internal_position)
{
  X9C10X dp0;

  dp0.begin(7, 8, 9);
  assertEqual(0, dp0.restoreInternalPosition(0));
  assertEqual(0, dp0.getPosition());
  assertEqual(50, dp0.restoreInternalPosition(50));
  assertEqual(50, dp0.getPosition());

  //  test truncation
  assertEqual(99, dp0.restoreInternalPosition(99));
  assertEqual(99, dp0.getPosition());
  assertEqual(99, dp0.restoreInternalPosition(100));
  assertEqual(99, dp0.getPosition());
  assertEqual(99, dp0.restoreInternalPosition(255));
  assertEqual(99, dp0.getPosition());
}


unittest(test_X9C10X_position)
{
  X9C10X dp0;

  dp0.begin(7, 8, 9);
  assertEqual(0, dp0.getPosition());

  fprintf(stderr, "setPosition step 19\n");
  for (uint8_t pos = 0; pos < 100; pos += 19)
  {
    assertEqual(pos, dp0.setPosition(pos));
    assertEqual(pos, dp0.getPosition());
  }

  //  test truncation
  assertEqual(99, dp0.setPosition(99));
  assertEqual(99, dp0.setPosition(100));
  assertEqual(99, dp0.setPosition(255));
}


unittest(test_X9C10X_store)
{
  X9C10X dp0;

  dp0.begin(7, 8, 9);

  fprintf(stderr, "store step 19\n");
  for (uint8_t pos = 0; pos < 100; pos += 19)
  {
    dp0.setPosition(pos);
    assertEqual(pos, dp0.store());
  }

  //  test truncation
  dp0.setPosition(99);
  assertEqual(99, dp0.store());
  dp0.setPosition(100);
  assertEqual(99, dp0.store());
  dp0.setPosition(255);
  assertEqual(99, dp0.store());
}


unittest(test_X9C10X_incr_decr)
{
  X9C10X dp0;

  dp0.begin(7, 8, 9);
  assertEqual(0, dp0.getPosition());

  dp0.setPosition(0);
  for (uint8_t pos = 0; pos < 10; pos++)
  {
    assertEqual(pos, dp0.getPosition());
    assertTrue(dp0.incr());
  }

  for (uint8_t pos = 0; pos < 5; pos++)
  {
    assertEqual(10 - pos, dp0.getPosition());
    assertTrue(dp0.decr());
  }
  
  dp0.setPosition(100);
  assertEqual(99, dp0.getPosition());
  assertFalse(dp0.incr());
  assertTrue(dp0.decr());
  assertTrue(dp0.incr());
  
  dp0.setPosition(0);
  assertEqual(0, dp0.getPosition());
  assertFalse(dp0.decr());
  assertTrue(dp0.incr());
  assertTrue(dp0.decr());
}


unittest(test_X9C10X_getOhm)
{
  X9C10X dp0;

  dp0.begin(7, 8, 9);
  assertEqual(0, dp0.getPosition());
  assertEqual(10000, dp0.getMaxOhm());

  for (uint8_t pos = 0; pos < 100; pos += 9)
  {
    fprintf(stderr, "VALUE: %d %d Ω\n", dp0.getPosition(), dp0.getOhm());
    assertTrue(dp0.incr());
  }

}


unittest(test_X9C10X_Ohm2Position)
{
  X9C10X dp0(1000);

  dp0.begin(7, 8, 9);
  assertEqual(0, dp0.getPosition());
  assertEqual(1000, dp0.getMaxOhm());

  for (uint16_t ohm = 0; ohm < 1000; ohm += 50)
  {
    fprintf(stderr, "OHM: %d Ω \tPOS: %d \tPOS: %d\n", ohm, 
                      dp0.Ohm2Position(ohm), dp0.Ohm2Position(ohm, true));
  }
}


unittest_main()

// --------
