//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-10-31
// PURPOSE: unit tests for the ellipse
//          https://github.com/RobTillaart/ellipse
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


#include "ellipse.h"


unittest_setup()
{
  fprintf(stderr, "ELLIPSE_LIB_VERSION: %s\n", (char*) ELLIPSE_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  ellipse E(1.0, 1.0);
  fprintf(stderr, "%03.8f\n", E.getA());
  fprintf(stderr, "%03.8f\n", E.getB());
  fprintf(stderr, "%03.8f\n", E.getC());
  fprintf(stderr, "%03.8f\n", E.area());
  fprintf(stderr, "%03.8f\n", E.circumference());
  fprintf(stderr, "%03.8f\n", E.perimeter_ref());
  fprintf(stderr, "%03.8f\n", E.perimeter_Keppler());
  fprintf(stderr, "%03.8f\n", E.perimeter_Ramanujan1());
  fprintf(stderr, "%03.8f\n", E.perimeter_Ramanujan2());
  fprintf(stderr, "%03.8f\n", E.eccentricity());
  fprintf(stderr, "\n");

  E.setA(1.0);
  E.setB(0.5);
  fprintf(stderr, "%03.8f\n", E.getA());
  fprintf(stderr, "%03.8f\n", E.getB());
  fprintf(stderr, "%03.8f\n", E.getC());
  fprintf(stderr, "%03.8f\n", E.area());
  fprintf(stderr, "%03.8f\n", E.circumference());
  fprintf(stderr, "%03.8f\n", E.perimeter_ref());
  fprintf(stderr, "%03.8f\n", E.perimeter_Keppler());
  fprintf(stderr, "%03.8f\n", E.perimeter_Ramanujan1());
  fprintf(stderr, "%03.8f\n", E.perimeter_Ramanujan2());
  fprintf(stderr, "%03.8f\n", E.eccentricity());

}


unittest_main()

// --------
