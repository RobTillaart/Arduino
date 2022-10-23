//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-10-20
// PURPOSE: unit tests for Arduino library for modulo mapping
//          https://github.com/RobTillaart/moduloMap
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
#include "moduloMap.h"


unittest_setup()
{
    fprintf(stderr, "MODMAP_LIB_VERSION: %s\n", (char *) MODMAP_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(1, 1);
}


unittest(test_map)
{
  // to elaborate
  MODMAP mm;
  mm.begin(0, 1);

  float x = mm.map(25.3);
  assertEqualFloat(0.3, x, 0.001);
}

unittest(test_begin)
{
  MODMAP mm;

  assertTrue(mm.begin(0, 1));
  assertFalse(mm.begin(1, 0));
  assertFalse(mm.begin(1, 1));
}



unittest_main()


// -- END OF FILE --
