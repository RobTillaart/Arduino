//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2020-12-08
// PURPOSE: unit tests for the AD520X digital potentiometers
//          https://github.com/RobTillaart/AD520X
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
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
#include "Kurtosis.h"


unittest_setup()
{
}


unittest_teardown()
{
}


unittest(test_begin)
{
  fprintf(stderr, "KURTOSIS_LIB_VERSION:\t%s\n", (char *) KURTOSIS_LIB_VERSION);
}


unittest(test_one)
{
  Kurtosis K;

  K.reset();
  assertEqual(K.count(), 0);

  for (int i = 0; i < 100; i++)
  {
    int x = i;
    K.add(x);
  }
  assertEqual(K.count(), 100);

  assertEqualFloat(K.mean(),      49.50, 0.01);
  assertEqualFloat(K.variance(), 841.67, 0.01);
  assertEqualFloat(K.stddev(),    29.01, 0.01);
  assertEqualFloat(K.skewness(),   0.00, 0.01);
  assertEqualFloat(K.kurtosis(),  -1.20, 0.01);
}



unittest_main()

//  -- END OF FILE --
