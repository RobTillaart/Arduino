//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-10-16
// PURPOSE: unit tests for the logic library
//     URL: https://github.com/RobTillaart/logic
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
#include "logic.h"


unittest_setup()
{
  fprintf(stderr, "LOGIC_LIB_VERSION: %s\n", (char *) LOGIC_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(1, 1);
}


unittest(test_constructor)
{
  logic lgc;
  assertEqual(0, lgc.getTable());
}

unittest(test_AND_OR_XOR)
{
  logic lgc;

  lgc.setTable(0b1000);  //  AND
  assertFalse(lgc.eval(0,0));
  assertFalse(lgc.eval(0,1));
  assertFalse(lgc.eval(1,0));
  assertTrue(lgc.eval(1,1));

  lgc.setTable(0b1110);  //  OR
  assertFalse(lgc.eval(0,0));
  assertTrue(lgc.eval(0,1));
  assertTrue(lgc.eval(1,0));
  assertTrue(lgc.eval(1,1));

  lgc.setTable(0b0110);  //  XOR
  assertFalse(lgc.eval(0,0));
  assertTrue(lgc.eval(0,1));
  assertTrue(lgc.eval(1,0));
  assertFalse(lgc.eval(1,1));
}

unittest(test_add_remove)
{
  logic lgc;

  //  create an AND table
  lgc.add(lgc.index(1,1));
  assertFalse(lgc.eval(0,0));
  assertFalse(lgc.eval(0,1));
  assertFalse(lgc.eval(1,0));
  assertTrue(lgc.eval(1,1));

  //  change table to OR
  lgc.add(lgc.index(0,1));
  lgc.add(lgc.index(1,0));
  assertFalse(lgc.eval(0,0));
  assertTrue(lgc.eval(0,1));
  assertTrue(lgc.eval(1,0));
  assertTrue(lgc.eval(1,1));

  //  change table to XOR
  lgc.remove(lgc.index(1,1));
  assertFalse(lgc.eval(0,0));
  assertTrue(lgc.eval(0,1));
  assertTrue(lgc.eval(1,0));
  assertFalse(lgc.eval(1,1));
}


unittest_main()


//  -- END OF FILE --

