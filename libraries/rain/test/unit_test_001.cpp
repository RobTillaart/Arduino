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


unittest(test_dryReference)
{
  RAIN rainSensor(0, 255);

  for (int ref = 0; ref < 5000; ref += 500)
  {
    rainSensor.setDryReference(ref);
    assertEqualFloat(ref, rainSensor.getDryReference(), 0.001);
  }
}


unittest(test_percentage)
{
  RAIN rainSensor(0, 255);

  assertEqual(100, rainSensor.percentage());
  //  EXTEND ?
}


unittest(test_delta)
{
  RAIN rainSensor(0, 255);

  assertEqual(0, rainSensor.delta());
  //  EXTEND ?
}


unittest(test_level)
{
  RAIN rainSensor(0, 255);

  assertTrue(rainSensor.setLevel(1, 1000));
  assertTrue(rainSensor.setLevel(2, 2000));
  assertTrue(rainSensor.setLevel(3, 3000));
  assertTrue(rainSensor.setLevel(4, 4000));
  assertFalse(rainSensor.setLevel(0, 1000));
  assertFalse(rainSensor.setLevel(5, 1000));
}


unittest(test_powerDelay)
{
  RAIN rainSensor(0, 255);

  for (int i = 0; i < 250; i+= 50)
  {
    rainSensor.setPowerDelay(i);
    assertEqual(i, rainSensor.getPowerDelay() );
  }
}


unittest_main()


//  -- END OF FILE --
