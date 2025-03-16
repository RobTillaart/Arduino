//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-03-16
// PURPOSE: unit tests for the PCA9671 library
//     URL: https://github.com/RobTillaart/PCA9671
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
#include "PCA9671.h"


unittest_setup()
{
  fprintf(stderr, "PCA9671_LIB_VERSION: %s\n", (char *) PCA9671_LIB_VERSION);
}



unittest(test_constants)
{
  assertEqual(PCA9671_INITIAL_VALUE, 0xFFFF);
  assertEqual(PCA9671_OK           , 0x00);
  assertEqual(PCA9671_PIN_ERROR    , 0x81);
  assertEqual(PCA9671_I2C_ERROR    , 0x82);
}


unittest(test_begin)
{
  PCA9671 PCA(0x38);

  Wire.begin();
  PCA.begin();

  int readValue = PCA.read16();
  assertEqual(0, readValue);

  int I2Cerror = PCA9671_I2C_ERROR;
  assertEqual(I2Cerror, PCA.lastError());
}


unittest(test_read)
{
  PCA9671 PCA(0x38);
  int readValue;

  Wire.begin();

  PCA.begin();
  for (int i = 0; i < 8; i++)
  {
    fprintf(stderr, "line %d\n", i);
    readValue = PCA.read(i);
    assertEqual(0, readValue);

    int I2Cerror = PCA9671_I2C_ERROR;
    assertEqual(I2Cerror, PCA.lastError());
  }

  fprintf(stderr, "test PCA9671_PIN_ERROR\n");
  readValue = PCA.read(16);
  assertEqual(0, readValue);
  int PINerror = PCA9671_PIN_ERROR;
  assertEqual(PINerror, PCA.lastError());
}


unittest_main()


//  -- END OF FILE --

