//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the Histogram
//          https://github.com/RobTillaart/Histogram
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
#include "histogram.h"



unittest_setup()
{
  fprintf(stderr, "HISTOGRAM_LIB_VERSION: %s\n", (char *) HISTOGRAM_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  float diceValues[] = {0.5, 1.5, 2.5, 3.5, 4.5, 5.5 };
  Histogram hist(6, diceValues);
  assertEqual(7, hist.size());
  assertEqual(0, hist.count());

  for (int i = 0; i < 7; i++)
  {
    fprintf(stderr, "%d\t", i);
    assertEqual(0, hist.bucket(i));
  }
}


unittest(test_dice)
{
  float diceValues[] = { 0.5, 1.5, 2.5, 3.5, 4.5, 5.5 };
  Histogram hist(6, diceValues);
  assertEqual(7, hist.size());
  assertEqual(0, hist.count());

  for (int d = 0; d < 70; d++)
  {
    hist.add( d % 7 ); // simulate dice 
  }

  assertEqual(7, hist.size());
  assertEqual(70, hist.count());

  for (int i = 0; i < 7; i++)
  {
    fprintf(stderr, "%d\t", i);
    assertEqual(10, hist.bucket(i));
  }

  hist.clear();
  assertEqual(7, hist.size());
  assertEqual(0, hist.count());

  for (int i = 0; i < 7; i++)
  {
    fprintf(stderr, "%d\t", i);
    assertEqual(0, hist.bucket(i));
  }
}


unittest_main()


//  -- END OF FILE --

