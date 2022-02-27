//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-02-27
// PURPOSE: unit tests for the GST library
//          https://github.com/RobTillaart/GST
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
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
#include "GST.h"



unittest_setup()
{
  fprintf(stderr, "GST_LIB_VERSION: %s\n", (char *) GST_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  GST gst;

  // default 0;
  assertEqualFloat(gst.getTruePositive()  , 0, 0.001);
  assertEqualFloat(gst.getTrueNegative()  , 0, 0.001);
  assertEqualFloat(gst.getFalsePositive() , 0, 0.001);
  assertEqualFloat(gst.getFalseNegative() , 0, 0.001);
  assertEqualFloat(gst.getTotal()         , 0, 0.001);
  assertEqualFloat(gst.getActualPositive(), 0, 0.001);
  assertEqualFloat(gst.getActualNegative(), 0, 0.001);
  assertEqualFloat(gst.getTestedPositive(), 0, 0.001);
  assertEqualFloat(gst.getTestedNegative(), 0, 0.001);
}


unittest(test_add)
{
  GST gst;

  gst.setTruePositive(100);
  gst.setTrueNegative(100);
  gst.setFalsePositive(100);
  gst.setFalseNegative(100);

  assertEqualFloat(gst.getTruePositive()  , 100, 0.001);
  assertEqualFloat(gst.getTrueNegative()  , 100, 0.001);
  assertEqualFloat(gst.getFalsePositive() , 100, 0.001);
  assertEqualFloat(gst.getFalseNegative() , 100, 0.001);
  assertEqualFloat(gst.getTotal()         , 400, 0.001);
  assertEqualFloat(gst.getActualPositive(), 200, 0.001);
  assertEqualFloat(gst.getActualNegative(), 200, 0.001);
  assertEqualFloat(gst.getTestedPositive(), 200, 0.001);
  assertEqualFloat(gst.getTestedNegative(), 200, 0.001);
}


unittest(test_one)
{
  GST gst;

  gst.setTruePositive(653);
  gst.setTrueNegative(312);
  gst.setFalsePositive(124);
  gst.setFalseNegative(423);

  assertEqualFloat(gst.sensitivity(), 0.6069, 0.0001);
  assertEqualFloat(gst.specificity(), 0.7156, 0.0001);

  assertEqualFloat(gst.TPR(), 0.6069, 0.0001);
  assertEqualFloat(gst.FNR(), 0.3931, 0.0001);
  assertEqualFloat(gst.FPR(), 0.2844, 0.0001);
  assertEqualFloat(gst.TNR(), 0.7156, 0.0001);

  assertEqualFloat(gst.PPV(), 0.8404, 0.0001);
  assertEqualFloat(gst.NPV(), 0.4245, 0.0001);
  assertEqualFloat(gst.FDR(), 0.1596, 0.0001);
  assertEqualFloat(gst.FOR(), 0.5755, 0.0001);
}


unittest_main()

// --------
