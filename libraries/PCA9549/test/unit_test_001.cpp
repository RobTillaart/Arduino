//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2023-12-12
// PURPOSE: unit tests for the PCA9549 I2C octal bus switch.
//          https://github.com/RobTillaart/PCA9549
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

/*
  most unit tests will test for fail
  as there is no sensor connected
  and there is no mockup.

  It appears that Wire.write does not fail without sensor...
*/


#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "PCA9549.h"


int expect;  //  TODO needed as there seems a problem with 8 bit comparisons (char?)

uint32_t start, stop;


unittest_setup()
{
  fprintf(stderr, "PCA9549_LIB_VERSION: %s\n", (char *) PCA9549_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0, PCA9549_OK);
}


unittest(test_constructor)
{
  PCA9549 pca(0x70);

  Wire.begin();

  assertTrue(pca.begin());
  assertTrue(pca.isConnected());
}


unittest(test_enable)
{
  PCA9549 pca(0x70);

  Wire.begin();

  bool b = pca.begin();
  assertEqual(b, true);

  uint8_t mask = 0x00;
  for (int chan = 0; chan < 8; chan++)
  {
    pca.enableChannel(chan);
    assertTrue(pca.isEnabled(chan));
  }
  assertEqual(0xFF, pca.getChannelMask());
  pca.setChannelMask(0x00);
  assertEqual(0x00, pca.getChannelMask());
}


unittest(test_select)
{
  PCA9549 pca(0x70);

  Wire.begin();

  bool b = pca.begin();
  assertEqual(b, true);

  uint8_t mask = 0x00;
  for (int chan = 0; chan < 8; chan++)
  {
    pca.selectChannel(chan);
    assertTrue(pca.isEnabled(chan));
  }
  assertEqual(0x80, pca.getChannelMask());
  pca.setChannelMask(0x00);
  assertEqual(0x00, pca.getChannelMask());
}


unittest_main()


//  -- END OF FILE --

