//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-10-26
// PURPOSE: unit tests for the RLCBuffer library
//     URL: https://github.com/RobTillaart/RLCBuffer
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
#include "RLCBuffer.h"


unittest_setup()
{
  fprintf(stderr, "RLCBUFFER_LIB_VERSION: %s\n", (char *) RLCBUFFER_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0x00, RLCBUFFER_OK);
}


unittest(test_constructor)
{
  RLCBuffer RLCB(10);
  
  assertEqual(10, RLCB.size());
  assertEqual(0, RLCB.count());
  
}


unittest_main()


//  -- END OF FILE --

