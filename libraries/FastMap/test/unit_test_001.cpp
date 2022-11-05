//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-21
// PURPOSE: unit tests for the FastMap
//          https://github.com/RobTillaart/FastMap
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
#include "FastMap.h"


unittest_setup()
{
  fprintf(stderr, "FASTMAP_LIB_VERSION: %s\n", (char *) FASTMAP_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_init)
{
  FastMap fm;
  FastMapDouble fmd;

  assertTrue(fm.init(-2, 12, 17, 42));
  assertFalse(fm.init(12, 12, 17, 42));
  assertFalse(fm.init(-2, 12, 17, 17));
  assertFalse(fm.init(12, 12, 17, 17));

  assertTrue(fmd.init(-2, 12, 17, 42));
  assertFalse(fmd.init(12, 12, 17, 42));
  assertFalse(fmd.init(-2, 12, 17, 17));
  assertFalse(fmd.init(12, 12, 17, 17));
}


unittest(test_map)
{
  FastMap fm;

  fm.init(-2, 12, 17, 42);

  assertEqualFloat(11.6429, fm.map(-5), 0.001);
  assertEqualFloat(17, fm.map(-2), 0.001);
  assertEqualFloat(20.5714, fm.map(0), 0.001);
  assertEqualFloat(26.1814, fm.map(PI), 0.001);
  assertEqualFloat(42, fm.map(12), 0.001);
  assertEqualFloat(47.3571, fm.map(15), 0.001);
}


unittest(test_back)
{
  FastMap fm;

  fm.init(-2, 12, 17, 42);

  assertEqualFloat(-14.32, fm.back(-5), 0.001);
  assertEqualFloat(-11.52, fm.back(0), 0.001);
  assertEqualFloat(-5.92, fm.back(10), 0.001);
  assertEqualFloat(-2, fm.back(17), 0.001);
  assertEqualFloat(2.48, fm.back(25), 0.001);
  assertEqualFloat(12, fm.back(42), 0.001);
  assertEqualFloat(24.88, fm.back(65), 0.001);
}


unittest(test_constrainedMap)
{
  FastMap fm;

  fm.init(-2, 12, 17, 42);

  assertEqualFloat(17, fm.constrainedMap(-5), 0.001);
  assertEqualFloat(17, fm.constrainedMap(-2), 0.001);
  assertEqualFloat(20.5714, fm.constrainedMap(0), 0.001);
  assertEqualFloat(26.1814, fm.constrainedMap(PI), 0.001);
  assertEqualFloat(42, fm.constrainedMap(12), 0.001);
  assertEqualFloat(42, fm.constrainedMap(15), 0.001);
}


unittest(test_lowerConstrainedMap)
{
  FastMap fm;

  fm.init(-2, 12, 17, 42);

  assertEqualFloat(17, fm.lowerConstrainedMap(-5), 0.001);
  assertEqualFloat(17, fm.lowerConstrainedMap(-2), 0.001);
  assertEqualFloat(20.5714, fm.lowerConstrainedMap(0), 0.001);
  assertEqualFloat(26.1814, fm.lowerConstrainedMap(PI), 0.001);
  assertEqualFloat(42, fm.lowerConstrainedMap(12), 0.001);
  assertEqualFloat(47.3571, fm.lowerConstrainedMap(15), 0.001);
}


unittest(test_upperConstrainedMap)
{
  FastMap fm;

  fm.init(-2, 12, 17, 42);

  assertEqualFloat(11.6429, fm.upperConstrainedMap(-5), 0.001);
  assertEqualFloat(17, fm.upperConstrainedMap(-2), 0.001);
  assertEqualFloat(20.5714, fm.upperConstrainedMap(0), 0.001);
  assertEqualFloat(26.1814, fm.upperConstrainedMap(PI), 0.001);
  assertEqualFloat(42, fm.upperConstrainedMap(12), 0.001);
  assertEqualFloat(42, fm.upperConstrainedMap(15), 0.001);
}


unittest(test_map_double)
{
  fprintf(stderr, "FAST MAP DOUBLE\n");

  FastMapDouble fm;

  fm.init(-2, 12, 17, 42);

  assertEqualFloat(11.6429, fm.map(-5), 0.001);
  assertEqualFloat(17, fm.map(-2), 0.001);
  assertEqualFloat(20.5714, fm.map(0), 0.001);
  assertEqualFloat(26.1814, fm.map(PI), 0.001);
  assertEqualFloat(42, fm.map(12), 0.001);
  assertEqualFloat(47.3571, fm.map(15), 0.001);
}


unittest_main()

// --------
