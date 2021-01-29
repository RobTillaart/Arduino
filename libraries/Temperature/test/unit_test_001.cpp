//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-01
// PURPOSE: unit tests for the temperature library
//          https://github.com/RobTillaart/Temperature
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
#include "temperature.h"



unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_conversion)
{
  fprintf(stderr, "VERSION: %s\n", TEMPERATURE_VERSION);
  
  assertEqualFloat(-40, Fahrenheit(-40), 0.001);
  assertEqualFloat(-40, Celsius(-40), 0.001);
  assertEqualFloat(273.15, Kelvin(0), 0.001);
}


unittest(test_dewpoint)
{
  assertEqualFloat(9.27985, dewPoint(20, 50), 0.001);
  assertEqualFloat(9.25489, dewPointFast(20, 50), 0.001);
  assertEqualFloat(21.2829, humidex(20, 10),  0.001);
}


unittest(test_heatIndex)
{
  assertEqualFloat(206.46,  heatIndex(20, 50), 0.001);
  assertEqualFloat(77.3509, heatIndex(68, 50), 0.001);
  assertEqualFloat(25.1949, heatIndexC(20, 50), 0.001);
}


unittest(test_windChill)
{
  assertEqualFloat(107.108, WindChill_F_mph (100, 10, true), 0.001);
  assertEqualFloat(40.8862, WindChill_C_kmph(37, 10, true),  0.001);
  assertEqualFloat(41.9713, WindChill_C_mps (37, 10, true),  0.001);
  assertEqualFloat(166.99,  WindChill_F_mph (100, 10, false), 0.001);
  assertEqualFloat(69.1205, WindChill_C_kmph(37, 10, false),  0.001);
  assertEqualFloat(154.934, WindChill_C_mps (37, 10, false),  0.001);
}


unittest_main()

// --------
