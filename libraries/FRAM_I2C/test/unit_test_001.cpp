//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-23
// PURPOSE: unit tests for the FRAM library
//          https://github.com/RobTillaart/FRAM_I2C
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


#include "FRAM.h"



unittest_setup()
{
  fprintf(stderr, "FRAM_LIB_VERSION: %s\n", (char*) FRAM_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(  0, FRAM_OK           );
  assertEqual(-10, FRAM_ERROR_ADDR   );
  assertEqual(-11, FRAM_ERROR_I2C    );
  assertEqual(-12, FRAM_ERROR_CONNECT);

  assertEqual(512,    FRAM_MB85RC04  );
  assertEqual(2048,   FRAM_MB85RC16  );
  assertEqual(8192,   FRAM_MB85RC64T );
  assertEqual(8192,   FRAM_MB85RC64V );
  assertEqual(16384,  FRAM_MB85RC128A);
  assertEqual(32768,  FRAM_MB85RC256V);
  assertEqual(65536,  FRAM_MB85RC512T);
  assertEqual(131072, FRAM_MB85RC1MT );
}


unittest(test_constructor)
{
  FRAM fram49;
  FRAM fram50;
  FRAM fram52;
  FRAM fram57;

  Wire.begin();

  fprintf(stderr, "\n Different constructors\n");
  assertEqual(FRAM_ERROR_ADDR, fram49.begin(0x49));
  assertEqual(FRAM_OK, fram50.begin());
  assertEqual(FRAM_OK, fram52.begin(0x52));
  assertEqual(FRAM_OK, fram57.begin(0x57, 4));

  fprintf(stderr, "\n no writeProtect pin defined\n");
  assertFalse(fram50.setWriteProtect(true));
  assertFalse(fram50.getWriteProtect());
  assertFalse(fram50.setWriteProtect(false));
  assertFalse(fram50.getWriteProtect());

  fprintf(stderr, "\n writeProtect pin defined\n");
  assertTrue(fram57.setWriteProtect(true));
  assertTrue(fram57.getWriteProtect());
  assertTrue(fram57.setWriteProtect(false));
  assertFalse(fram57.getWriteProtect());

  fprintf(stderr, "\n all fail as nothing connected\n");
  assertEqual(0xFFF, fram50.getManufacturerID());
  assertEqual(0xFFF, fram50.getProductID());
  assertEqual(0, fram50.getSize());
}


unittest(test_getSizeBytes)
{
  FRAM fram;

  Wire.begin();

  assertEqual(0, fram.getSizeBytes());
  fram.setSizeBytes(FRAM_MB85RC256V);
  assertEqual(32768, fram.getSizeBytes());

  FRAM32 f32;
  assertEqual(0, f32.getSizeBytes());
  f32.setSizeBytes(FRAM_MB85RC1MT);
  assertEqual(131072, f32.getSizeBytes());

  FRAM11 f11;
  assertEqual(2, f11.getSize());
  assertEqual(2048, f11.getSizeBytes());

  FRAM9 f9;
  assertEqual(0, f9.getSize());
  assertEqual(512, f9.getSizeBytes());
}


unittest(test_clear)
{
  FRAM fram;

  Wire.begin();

  // note size is not set.
  assertEqual(0, fram.clear());
  assertEqual(0, fram.clear(0xFF));
}


unittest_main()


//  -- END OF FILE --

