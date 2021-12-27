//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-05-29
// PURPOSE: unit tests for the relativity library
//          https://github.com/RobTillaart/relativity
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


#include "relativity.h"


unittest_setup()
{
  fprintf(stderr, "RELATIVITY_LIB_VERSION: %s\n", (char*) RELATIVITY_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  relativity R;

  // test constants
  assertEqualFloat(299792458.0, R.getC(), 1);
  assertEqualFloat(6.6742e-11, R.getG(), 1e-15);
  fprintf(stderr, "done...\n");
}


unittest(test_alpha_gamma)
{
  relativity R;

  assertEqualFloat(1.0, R.factor(0), 0.0001);
  assertEqualFloat(0.0, R.factor(R.getC()), 0.0001);

  assertEqualFloat(1.0, R.gamma(0), 0.0001);
  assertInfinity(R.gamma(R.getC()) );

  fprintf(stderr, "\n\tperc\t\tspeed\t\tfactor\t\tgamma\n");
  for (double perc = 1; perc < 99.9999; perc += (100 - perc) / 10)
  {
    double v = R.getC() * perc * 0.01;
    fprintf(stderr, "\t%.4f\t\t%.4f\t%.6f\t%.6f\n", perc, v * 0.001, R.factor(v), R.gamma(v));
  }
  fprintf(stderr, "done...\n");
}


unittest(test_relativeTime)
{
  relativity R;

  assertEqualFloat(1.0, R.relativeTime(1, 0), 0.0001);
  assertEqualFloat(0.0, R.relativeTime(1, R.getC()), 0.0001);

  fprintf(stderr, "\n\tperc\t\tspeed\t\ttime\n");
  for (double perc = 1; perc < 99.9999; perc += (100 - perc) / 10)
  {
    double v = R.getC() * perc * 0.01;
    fprintf(stderr, "\t%.4f\t\t%.4f\t%.6f\t\n", perc, v * 0.001, R.relativeTime(1, v));
  }
  fprintf(stderr, "done...\n");
}


unittest(test_relativeLength)
{
  relativity R;

  assertEqualFloat(1.0, R.relativeLength(1, 0), 0.0001);
  assertEqualFloat(0.0, R.relativeLength(1, R.getC()), 0.0001);

  fprintf(stderr, "\n\tperc\t\tspeed\t\tlength\n");
  for (double perc = 1; perc < 99.9999; perc += (100 - perc) / 10)
  {
    double v = R.getC() * perc * 0.01;
    fprintf(stderr, "\t%.4f\t\t%.4f\t%.6f\t\n", perc, v * 0.001, R.relativeLength(1, v));
  }
  fprintf(stderr, "done...\n");
}


unittest(test_relativeMass)
{
  relativity R;

  assertEqualFloat(1.0, R.relativeMass(1, 0), 0.0001);
  assertInfinity(R.relativeMass(1, R.getC()) );

  fprintf(stderr, "\n\tperc\t\tspeed\t\tmass\n");
  for (double perc = 1; perc < 99.9999; perc += (100 - perc) / 10)
  {
    double v = R.getC() * perc * 0.01;
    fprintf(stderr, "\t%.4f\t\t%.4f\t%.4f\t\n", perc, v * 0.001, R.relativeMass(1, v));
  }
  fprintf(stderr, "done...\n");
}


unittest(test_EnergyMass)
{
  relativity R;

  assertEqualFloat(8.98755e+16, R.EnergyMass(1, 0), 1e11);
  assertInfinity(R.EnergyMass(1, R.getC()) );

  fprintf(stderr, "\n\tperc\t\tspeed\t\tenergy\n");
  for (double perc = 1; perc < 99.9999; perc += (100 - perc) / 10)
  {
    double v = R.getC() * perc * 0.01;
    fprintf(stderr, "\t%.4f\t\t%.4f\t%e\t\n", perc, v * 0.001, R.EnergyMass(1, v));
  }
  fprintf(stderr, "done...\n");
}


unittest(test_gravitationalTime)
{
  relativity R;

  assertEqualFloat(6.6742e-11, R.getG(), 1e-15);

  fprintf(stderr, "\n\tplanet\tmass\t\tradius\t\t1 - time\n");
  for (uint8_t p = 0; p < 10; p++)
  {
    double m = R.getPlanetMass(p);
    double r = R.getPlanetRadius(p);
    fprintf(stderr, "\t%d\t%e\t%e\t%e\n", p, m, r, 1 - R.gravitationalTime(1, m, r));
  }
  fprintf(stderr, "done...\n");
}


unittest(test_radiusEarth)
{
  relativity R;

  assertEqualFloat(6357, R.radiusEarth(90), 0.001);
  assertEqualFloat(6378, R.radiusEarth(00), 0.001);

  fprintf(stderr, "\n\tlon\tdiameter\n");
  for (uint8_t lon = 0; lon < 91; lon +=3)
  {
    double dia = R.radiusEarth(lon);
    fprintf(stderr, "\t%d\t%0.1f\n", lon, dia);
  }
  fprintf(stderr, "done...\n");
}


unittest_main()


// --------
