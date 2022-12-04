//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-12-03
// PURPOSE: unit tests for the RAIN sensor
//          https://github.com/RobTillaart/RAIN
//          https://www.adafruit.com/product/2857
//          https://www.tinytronics.nl/shop/nl/sensoren/vloeistof/regensensor
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
#include "rain.h"


unittest_setup()
{
    fprintf(stderr, "RAIN_LIB_VERSION: %s\n", (char *) RAIN_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(1, 1);
}


unittest_main()


//  -- END OF FILE --
