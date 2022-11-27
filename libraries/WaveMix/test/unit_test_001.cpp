//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-03-24
// PURPOSE: unit tests for the WaveMix Library
//          https://github.com/RobTillaart/WaveMix
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
#include "WaveMix.h"



unittest_setup()
{
  fprintf(stderr, "WAVEMIX_LIB_VERSION: %s\n", (char *) WAVEMIX_LIB_VERSION);
}


unittest_teardown()
{
  
}


unittest(test_constructor)
{
  WaveMix wm;
  assertEqualFloat(0.5, wm.getW1(), 0.001); 
  assertEqualFloat(0.5, wm.getW2(), 0.001); 
}


unittest(test_setWeight)
{
  WaveMix wm;
  wm.setWeight(0.0, 3.0);
  assertEqualFloat(0.00, wm.getW1(), 0.001); 
  assertEqualFloat(1.00, wm.getW2(), 0.001); 
  wm.setWeight(1.0, 3.0);
  assertEqualFloat(0.25, wm.getW1(), 0.001); 
  assertEqualFloat(0.75, wm.getW2(), 0.001); 
  wm.setWeight(5.5, 0.0);
  assertEqualFloat(1.00, wm.getW1(), 0.001); 
  assertEqualFloat(0.00, wm.getW2(), 0.001); 

  assertTrue(wm.setWeight(0.0, 3.0));
  assertFalse(wm.setWeight(-3.0, 3.0));
}


unittest(test_setPercentage)
{
  WaveMix wm;
  wm.setPercentage(0);
  assertEqualFloat(0.00, wm.getW1(), 0.001); 
  assertEqualFloat(1.00, wm.getW2(), 0.001); 
  wm.setPercentage(25);
  assertEqualFloat(0.25, wm.getW1(), 0.001); 
  assertEqualFloat(0.75, wm.getW2(), 0.001); 
  wm.setPercentage(42);
  assertEqualFloat(0.42, wm.getW1(), 0.001); 
  assertEqualFloat(0.58, wm.getW2(), 0.001); 
  wm.setPercentage(73);
  assertEqualFloat(0.73, wm.getW1(), 0.001); 
  assertEqualFloat(0.27, wm.getW2(), 0.001); 
  wm.setPercentage(100);
  assertEqualFloat(1.00, wm.getW1(), 0.001); 
  assertEqualFloat(0.00, wm.getW2(), 0.001);
  
  assertTrue(wm.setPercentage(0));
  assertTrue(wm.setPercentage(100));
  assertFalse(wm.setPercentage(-1));
  assertFalse(wm.setPercentage(101));
}


unittest(test_mix)
{
  WaveMix wm;
  wm.setPercentage(25);
  for (int i = 0; i < 10; i++)
  {
    assertEqualFloat(3 + 0.25 * i, wm.mix(i, 4), 0.001);
  }
}

unittest_main()

// --------
