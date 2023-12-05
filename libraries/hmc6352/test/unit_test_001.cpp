//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-28
// PURPOSE: unit tests for the HMC6352 library
//          https://github.com/RobTillaart/HMC6352
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
#include "hmc6352.h"



unittest_setup()
{
  fprintf(stderr, "HMC6352_LIB_VERSION: %s\n", (char *) HMC6352_LIB_VERSION);
}

unittest_teardown()
{
}

/*
unittest(test_new_operator)
{
  assertEqualINF(exp(800));
  assertEqualINF(0.0/0.0);
  assertEqualINF(42);

  assertEqualNAN(INFINITY - INFINITY);
  assertEqualNAN(0.0/0.0);
  assertEqualNAN(42);
}
*/


unittest(test_constructor)
{
  hmc6352 Compass(0x21);

  Wire.begin();
  assertTrue(Compass.begin());
  assertTrue(Compass.isConnected());
}


unittest(test_constants)
{
  fprintf(stderr, "\nFunction return values\n");
  assertEqual(  0, HMC6532_OK);
  assertEqual(-20, HMC6352_ERROR_PARAM1);
  assertEqual(-21, HMC6352_ERROR_PARAM2);

  fprintf(stderr, "\nI2C status\n");
  assertEqual(  0, HMC6532_I2C_OK);
  assertEqual( -1, HMC6532_I2C_ERROR_BUFFEROVERFLOW);
  assertEqual( -2, HMC6532_I2C_ERROR_ADDR_NACK);
  assertEqual( -3, HMC6532_I2C_ERROR_DATA_NACK);
  assertEqual( -4, HMC6532_I2C_ERROR_OTHER);
  assertEqual(-10, HMC6352_I2C_ERROR_REQ_FROM);
}


unittest(test_setOperationalModus)
{
  hmc6352 Compass(0x21);

  Wire.begin();
  assertTrue(Compass.begin());
  assertTrue(Compass.isConnected());

  // mode error
  assertEqual(HMC6352_ERROR_PARAM1, Compass.setOperationalModus((hmcMode)3, 1, true));
  assertEqual(HMC6352_ERROR_PARAM1, Compass.setOperationalModus((hmcMode)255, 1, true));

  // freq error
  assertEqual(HMC6352_ERROR_PARAM2, Compass.setOperationalModus((hmcMode)0, 0, true));
  assertEqual(HMC6352_ERROR_PARAM2, Compass.setOperationalModus((hmcMode)0, 9, true));
  assertEqual(HMC6352_ERROR_PARAM2, Compass.setOperationalModus((hmcMode)0, 11, true));
  assertEqual(HMC6352_ERROR_PARAM2, Compass.setOperationalModus((hmcMode)0, 21, true));
}


unittest(test_setOutputModus)
{
  hmc6352 Compass(0x21);

  Wire.begin();
  assertTrue(Compass.begin());
  assertTrue(Compass.isConnected());

  // outputModus error
  assertEqual(HMC6352_ERROR_PARAM1, Compass.setOutputModus(5));
  assertEqual(HMC6352_ERROR_PARAM1, Compass.setOutputModus(255));
}


unittest(test_setI2CAddress)
{
  hmc6352 Compass(0x21);

  Wire.begin();
  assertTrue(Compass.begin());
  assertTrue(Compass.isConnected());

  // setI2CAddress error
  assertEqual(HMC6352_ERROR_PARAM1, Compass.setI2CAddress(0x00));
  assertEqual(HMC6352_ERROR_PARAM1, Compass.setI2CAddress(0x0F));
  assertEqual(HMC6352_ERROR_PARAM1, Compass.setI2CAddress(0xF7));
}


unittest_main()


//  -- END OF FILE --

