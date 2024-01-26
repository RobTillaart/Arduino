//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-02-12
// PURPOSE: unit tests for the AM2315C library
//          https://github.com/RobTillaart/AM2315C
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


#include "AM2315C.h"


unittest_setup()
{
  fprintf(stderr, "AM2315C_LIB_VERSION: %s \n", (char *) AM2315C_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(  0, AM2315C_OK);
  assertEqual(-10, AM2315C_ERROR_CHECKSUM);
  assertEqual(-11, AM2315C_ERROR_CONNECT);
  assertEqual(-12, AM2315C_MISSING_BYTES);
  assertEqual(-13, AM2315C_ERROR_BYTES_ALL_ZERO);
  assertEqual(-14, AM2315C_ERROR_READ_TIMEOUT);
  assertEqual(-15, AM2315C_ERROR_LASTREAD);
}


unittest(test_constructor)
{
  AM2315C DHT(&Wire);

  assertEqualFloat(0, DHT.getTemperature(), 0.001);
  assertEqualFloat(0, DHT.getHumidity(), 0.001);
  assertEqualFloat(0, DHT.getTempOffset(), 0.001);
  assertEqualFloat(0, DHT.getHumOffset(), 0.001);

  Wire.begin();
  DHT.begin();
  assertEqual(AM2315C_ERROR_LASTREAD, DHT.read());

  //  assertEqualFloat(0, DHT.getTemperature(), 0.001);
  //  assertEqualFloat(0, DHT.getHumidity(), 0.001);
  assertEqualFloat(0, DHT.getTempOffset(), 0.001);
  assertEqualFloat(0, DHT.getHumOffset(), 0.001);
}


unittest(test_offset)
{
  AM2315C DHT;  //  default Wire

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

