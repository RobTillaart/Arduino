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
  fprintf(stderr, "TEMPERATURE_LIB_VERSION: %s\n", (char *) TEMPERATURE_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_conversion)
{
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
  //  Fahrenheit
  assertEqualFloat(14.050, heatIndex(20, 50), 0.001);
  assertEqualFloat(66.850, heatIndex(68, 50), 0.001);
  //  Celsius
  assertEqualFloat(20.000, heatIndexC(20, 50), 0.001);
}


unittest(test_heatIndex_2)
{
  //  Fahrenheit  reference points
  assertEqualFloat( 77, heatIndex(80,  00), 1);
  assertEqualFloat( 78, heatIndex(80,  10), 1);
  assertEqualFloat( 80, heatIndex(80,  40), 1);
  assertEqualFloat( 82, heatIndex(80,  60), 1);
  assertEqualFloat( 86, heatIndex(80,  90), 1);
  assertEqualFloat( 89, heatIndex(80, 100), 1);
  fprintf(stderr, "\n");
  assertEqualFloat( 84, heatIndex(90,  00), 1);
  assertEqualFloat( 85, heatIndex(90,  10), 1);
  assertEqualFloat( 91, heatIndex(90,  40), 1);
  assertEqualFloat(100, heatIndex(90,  60), 1);
  assertEqualFloat(122, heatIndex(90,  90), 1);
  assertEqualFloat(132, heatIndex(90, 100), 1);
  fprintf(stderr, "\n");
  assertEqualFloat( 91, heatIndex(100,  00), 1);
  assertEqualFloat( 94, heatIndex(100,  10), 1);
  assertEqualFloat(109, heatIndex(100,  40), 1);
  assertEqualFloat(129, heatIndex(100,  60), 1);
  assertEqualFloat(176, heatIndex(100,  90), 1);
  assertEqualFloat(195, heatIndex(100, 100), 1);
  fprintf(stderr, "\n");
  assertEqualFloat( 99, heatIndex(110,  00), 1);
  assertEqualFloat(104, heatIndex(110,  10), 1);
  assertEqualFloat(136, heatIndex(110,  40), 1);
  assertEqualFloat(171, heatIndex(110,  60), 1);
  assertEqualFloat(247, heatIndex(110,  90), 1);
  assertEqualFloat(278, heatIndex(110, 100), 1);
}


unittest(test_windChill)
{
  fprintf(stderr, "\n Fahrenheit\n");
  assertEqualFloat( -15.9, WindChill_F_mph (0, 10, true), 0.1);
  assertEqualFloat(-321.8, WindChill_F_mph (0, 10, false), 0.1);

  fprintf(stderr, "\n Celsius\n");
  assertEqualFloat(  -3.3, WindChill_C_kmph(0, 10, true), 0.1);
  assertEqualFloat(  -7.1, WindChill_C_mps (0, 10, true), 0.1);
  assertEqualFloat( -24.3, WindChill_C_kmph(-20, 5, true), 0.1);
  assertEqualFloat(-100.5, WindChill_C_kmph(0, 10, false), 0.1);
  assertEqualFloat(-396.2, WindChill_C_mps (0, 10, false), 0.1);
}


unittest(test_converter)
{
  temperatureConverter TC;

  fprintf(stderr, "\n 0°C\n");
  TC.setCelsius(0);
  assertEqualFloat( 273.15, TC.getKelvin(),     0.01);
  assertEqualFloat(   0.00, TC.getCelsius(),    0.01);
  assertEqualFloat(  32.00, TC.getFahrenheit(), 0.01);
  assertEqualFloat(   0.00, TC.getReamur(),     0.01);
  assertEqualFloat( 491.67, TC.getRankine(),    0.01);
  assertEqualFloat(-100.00, TC.getDelisle(),    0.01);
  assertEqualFloat(   0.00, TC.getNewton(),     0.01);
  assertEqualFloat(   7.50, TC.getRomer(),      0.01);

  fprintf(stderr, "\n 100°C\n");
  TC.setCelsius(100);
  assertEqualFloat( 373.15, TC.getKelvin(),     0.01);
  assertEqualFloat( 100.00, TC.getCelsius(),    0.01);
  assertEqualFloat( 212.00, TC.getFahrenheit(), 0.01);
  assertEqualFloat(  80.00, TC.getReamur(),     0.01);
  assertEqualFloat( 671.67, TC.getRankine(),    0.01);
  assertEqualFloat(  50.00, TC.getDelisle(),    0.01);
  assertEqualFloat(  33.00, TC.getNewton(),     0.01);
  assertEqualFloat(  60.00, TC.getRomer(),      0.01);
}


unittest(test_set_get)
{
  temperatureConverter TC;

  fprintf(stderr, "\n 42°C\n");
  TC.setKelvin(42);
  assertEqualFloat( 42.00, TC.getKelvin(),     0.01);
  TC.setCelsius(42);
  assertEqualFloat( 42.00, TC.getCelsius(),    0.01);
  TC.setFahrenheit(42);
  assertEqualFloat( 42.00, TC.getFahrenheit(), 0.01);
  TC.setReamur(42);
  assertEqualFloat( 42.00, TC.getReamur(),     0.01);
  TC.setRankine(42);
  assertEqualFloat( 42.00, TC.getRankine(),    0.01);
  TC.setDelisle(42);
  assertEqualFloat( 42.00, TC.getDelisle(),    0.01);
  TC.setNewton(42);
  assertEqualFloat( 42.00, TC.getNewton(),     0.01);
  TC.setRomer(42);
  assertEqualFloat( 42.00, TC.getRomer(),      0.01);
}


unittest_main()

// --------
