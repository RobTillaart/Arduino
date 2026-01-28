//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-03-27
// PURPOSE: unit tests for the radiation library
//     URL: https://github.com/RobTillaart/ACD10
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
#include "radiation.h"


unittest_setup()
{
  fprintf(stderr, "RADIATION_LIB_VERSION: %s\n", (char *) RADIATION_LIB_VERSION);
}


unittest_teardown()
{
}



unittest(test_constructor)
{

  radiation R;


}


unittest_main()


//  -- END OF FILE --

