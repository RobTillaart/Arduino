//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the PCF8575 - 16 channel I2C IO expander.
//          https://github.com/RobTillaart/PCF8575
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual);               // a == b
// assertNotEqual(unwanted, actual);            // a != b
// assertComparativeEquivalent(expected, actual);    // abs(a - b) == 0 or (!(a > b) && !(a < b))
// assertComparativeNotEquivalent(unwanted, actual); // abs(a - b) > 0  or ((a > b) || (a < b))
// assertLess(upperBound, actual);              // a < b
// assertMore(lowerBound, actual);              // a > b
// assertLessOrEqual(upperBound, actual);       // a <= b
// assertMoreOrEqual(lowerBound, actual);       // a >= b
// assertTrue(actual);
// assertFalse(actual);
// assertNull(actual);

// // special cases for floats
// assertEqualFloat(expected, actual, epsilon);    // fabs(a - b) <= epsilon
// assertNotEqualFloat(unwanted, actual, epsilon); // fabs(a - b) >= epsilon
// assertInfinity(actual);                         // isinf(a)
// assertNotInfinity(actual);                      // !isinf(a)
// assertNAN(arg);                                 // isnan(a)
// assertNotNAN(arg);                              // !isnan(a)

#include <ArduinoUnitTests.h>


#include "Arduino.h"
#include "PCF8575.h"


PCF8575 PCF(0x38);


unittest_setup()
{
  fprintf(stderr, "PCF8575_LIB_VERSION: %s\n", (char *) PCF8575_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(PCF8575_INITIAL_VALUE, 0xFFFF);
  assertEqual(PCF8575_OK           , 0x00);
  assertEqual(PCF8575_PIN_ERROR    , 0x81);
  assertEqual(PCF8575_I2C_ERROR    , 0x82);
}


unittest(test_begin)
{
  PCF8575 PCF(0x38);

  Wire.begin();
  PCF.begin();

  int readValue = PCF.read16();
  assertEqual(0, readValue);

  int I2Cerror = PCF8575_I2C_ERROR;
  assertEqual(I2Cerror, PCF.lastError());
}


unittest(test_read)
{
  PCF8575 PCF(0x38);
  int readValue;

  Wire.begin();

  PCF.begin();
  for (int i = 0; i < 8; i++)
  {
    fprintf(stderr, "line %d\n", i);
    readValue = PCF.read(i);
    assertEqual(0, readValue);

    int I2Cerror = PCF8575_I2C_ERROR;
    assertEqual(I2Cerror, PCF.lastError());
  }

  fprintf(stderr, "test PCF8575_PIN_ERROR\n");
  readValue = PCF.read(16);
  assertEqual(0, readValue);
  int PINerror = PCF8575_PIN_ERROR;
  assertEqual(PINerror, PCF.lastError());
}


unittest_main()


//  -- END OF FILE --

