//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-09
// PURPOSE: unit tests for the ADT7470 Fan Monitoring library
//          https://github.com/RobTillaart/ADT7470
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

#include "ADT7470.h"


unittest_setup()
{
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  ADT7470 ADT(0x2C);
  ADT.begin();

  assertFalse(ADT.isConnected());
}


unittest_main()

// --------
