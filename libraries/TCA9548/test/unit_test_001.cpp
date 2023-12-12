//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2021-03-16
// PURPOSE: unit tests for the TCA9548 I2C multiplexer
//          https://github.com/RobTillaart/TCA9548
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
#include "TCA9548.h"


int expect;  //  TODO needed as there seems a problem with 8 bit comparisons (char?)

uint32_t start, stop;


unittest_setup()
{
  fprintf(stderr, "TCA9548_LIB_VERSION: %s\n", (char *) TCA9548_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0,   TCA9548_OK);
  assertEqual(-10, TCA9548_ERROR_I2C);
  assertEqual(-20, TCA9548_ERROR_CHANNEL);
}


unittest(test_constructor)
{
  TCA9548 tca(0x70);

  Wire.begin();

  assertTrue(tca.begin());
  assertTrue(tca.isConnected());
  assertEqual(8, tca.channelCount());
  
  PCA9548 pca8(0x71);
  assertTrue(pca8.begin());
  assertTrue(pca8.isConnected());
  assertEqual(8, pca8.channelCount());
  
  PCA9546 pca6(0x71);
  assertTrue(pca6.begin());
  assertTrue(pca6.isConnected());
  assertEqual(4, pca6.channelCount());
  
  PCA9545 pca5(0x71);
  assertTrue(pca5.begin());
  assertTrue(pca5.isConnected());
  assertEqual(4, pca5.channelCount());
  
  PCA9543 pca3(0x71);
  assertTrue(pca3.begin());
  assertTrue(pca3.isConnected());
  assertEqual(2, pca3.channelCount());
}


unittest(test_enable)
{
  TCA9548 tca(0x70);

  Wire.begin();

  bool b = tca.begin();
  assertEqual(b, true);

  uint8_t mask = 0x00;
  for (int chan = 0; chan < 8; chan++)
  {
    tca.enableChannel(chan);
    assertTrue(tca.isEnabled(chan));
  }
  assertEqual(0xFF, tca.getChannelMask());
  tca.setChannelMask(0x00);
  assertEqual(0x00, tca.getChannelMask());
}


unittest(test_select)
{
  TCA9548 tca(0x70);

  Wire.begin();

  bool b = tca.begin();
  assertEqual(b, true);

  uint8_t mask = 0x00;
  for (int chan = 0; chan < 8; chan++)
  {
    tca.selectChannel(chan);
    assertTrue(tca.isEnabled(chan));
  }
  assertEqual(0x80, tca.getChannelMask());
  tca.setChannelMask(0x00);
  assertEqual(0x00, tca.getChannelMask());
}


unittest_main()


//  -- END OF FILE --

