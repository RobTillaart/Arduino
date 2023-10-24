//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-19
// PURPOSE: unit tests for the DHT12 library
//          https://github.com/RobTillaart/DHT12
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


#include "Wire.h"
#include "DHT12.h"


unittest_setup()
{
  fprintf(stderr, "DHT12_LIB_VERSION: %s \n", (char *) DHT12_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(  0, DHT12_OK);
  assertEqual(-10, DHT12_ERROR_CHECKSUM);
  assertEqual(-11, DHT12_ERROR_CONNECT);
  assertEqual(-12, DHT12_MISSING_BYTES);
}


unittest(test_constructor)
{
  DHT12 DHT(&Wire);

  assertEqualFloat(0, DHT.getTemperature(), 0.001);
  assertEqualFloat(0, DHT.getHumidity(), 0.001);
  assertEqualFloat(0, DHT.getTempOffset(), 0.001);
  assertEqualFloat(0, DHT.getHumOffset(), 0.001);

  Wire.begin();
  DHT.begin();

  assertEqual(DHT12_ERROR_CONNECT, DHT.read());

  assertEqualFloat(0, DHT.getTemperature(), 0.001);
  assertEqualFloat(0, DHT.getHumidity(), 0.001);
  assertEqualFloat(0, DHT.getTempOffset(), 0.001);
  assertEqualFloat(0, DHT.getHumOffset(), 0.001);
}


unittest(test_offset)
{
  DHT12 DHT(&Wire);

  Wire.begin();
  DHT.begin();

  assertEqualFloat(0, DHT.getTempOffset(), 0.001);
  assertEqualFloat(0, DHT.getHumOffset(), 0.001);

  for (float offset = -1.5; offset < 1.5; offset += 0.5)
  {
    DHT.setHumOffset(offset);
    DHT.setTempOffset(offset);

    assertEqualFloat(offset, DHT.getTempOffset(), 0.001);
    assertEqualFloat(offset, DHT.getHumOffset(), 0.001);

    assertEqualFloat(offset, DHT.getTemperature(), 0.001);
    assertEqualFloat(offset, DHT.getHumidity(), 0.001);
  }
}


unittest_main()


//  -- END OF FILE --

