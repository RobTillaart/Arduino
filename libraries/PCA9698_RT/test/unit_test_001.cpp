//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2025-01-06
// PURPOSE: unit tests for the PCA9698 - I2C, 40 channel IO expander.
//          https://github.com/RobTillaart/PCA9698_RT
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
#include "PCA9698.h"


PCA9698 PCA(0x20);


unittest_setup()
{
  fprintf(stderr, "PCA9698_LIB_VERSION: %s\n", (char *) PCA9698_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0x00, PCA9698_OK        );
  assertEqual(0x81, PCA9698_PIN_ERROR );
  assertEqual(0x82, PCA9698_I2C_ERROR );
  assertEqual(0x83, PCA9698_BANK_ERROR);
}


unittest(test_constructor)
{
  PCA9698 PCA(0x20);

  Wire.begin();
  PCA.begin();

  assertEqual(0x20, PCA.getAddress());
  assertEqual(0x00, PCA.lastError());
}


unittest_main()


//  -- END OF FILE --

