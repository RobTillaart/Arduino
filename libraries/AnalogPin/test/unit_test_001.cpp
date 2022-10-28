//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-10
// PURPOSE: unit tests for the AnalogPin library
//          https://github.com/RobTillaart/SHT31
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
#include "AnalogPin.h"


unittest_setup()
{
  fprintf(stderr, "ANALOGPIN_LIB_VERSION: %s\n", (char *) ANALOGPIN_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  AnalogPin AP(0);        // A0 not supported

  assertEqual(7, AP.getPrescaler());
  assertEqual(0, AP.getSmoothWeight());
  assertEqual(0, AP.getNoiseThreshold());
  assertEqual(0, AP.read());
  assertEqual(0, AP.readSmoothed());
  assertEqual(0, AP.readLast());
  assertEqual(0, AP.readPrevious());
}


unittest(test_prescaler)
{
  AnalogPin AP(0); 

  // 0 and 1 are not allowed.
  AP.setPrescaler(0);
  assertNotEqual(0, AP.getPrescaler());
  AP.setPrescaler(1);
  assertNotEqual(1, AP.getPrescaler());

  for (int i = 2; i < 8; i++)
  {
    AP.setPrescaler(i);
    assertEqual(i, AP.getPrescaler());
  }
}


unittest(test_noiseThreshold)
{
  AnalogPin AP(0);

  for (int i = 0; i < 31; i += 6)
  {
    AP.setNoiseThreshold(i);
    assertEqual(i, AP.getNoiseThreshold());
  }
}


unittest(test_smooth)
{
  AnalogPin AP(0);

  for (int i = 0; i < 31; i += 6)
  {
    AP.setSmoothWeight(i);
    assertEqual(i, AP.getSmoothWeight());
  }
}


unittest(test_read)
{
  AnalogPin AP(0);
  assertEqual(1, 1);

  // TODO unit test cannot read analogPort yet
  // assertEqual(0, AP.read());
  // assertEqual(0, AP.readSmoothed());
  // assertEqual(0, AP.readLast());
  // assertEqual(0, AP.readPrevious());
}


unittest_main()

// --------
