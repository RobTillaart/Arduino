//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-08-29
// PURPOSE: unit tests for VolumeConverter class
//          https://github.com/RobTillaart/VolumeConverter
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
#include "VolumeConverter.h"



unittest_setup()
{
  fprintf(stderr, "VOLUMECONVERTER_LIB_VERSION: %s\n", (char *) VOLUMECONVERTER_LIB_VERSION);
}


unittest_teardown()
{
  fprintf(stderr, "\n");
}


unittest(test_VolumeConverter)
{
  VolumeConverter VC;

  fprintf(stderr, "setLiters\n");
  VC.setLiters(1);
  assertEqualFloat(1, VC.getLiters(), 0.0001);

  fprintf(stderr, "setMilliLiters\n");
  VC.setMilliLiters(1);
  assertEqualFloat(1, VC.getMilliLiters(), 0.0001);

  fprintf(stderr, "setCubicMeters\n");
  VC.setCubicMeters(1);
  assertEqualFloat(1, VC.getCubicMeters(), 0.0001);

  fprintf(stderr, "setLongTons\n");
  VC.setLongTons(1);
  assertEqualFloat(1, VC.getLongTons(), 0.0001);

  fprintf(stderr, "setShortTons\n");
  VC.setShortTons(1);
  assertEqualFloat(1, VC.getShortTons(), 0.0001);

  fprintf(stderr, "setBarrels\n");
  VC.setBarrels(1);
  assertEqualFloat(1, VC.getBarrels(), 0.0001);

  fprintf(stderr, "setGallons\n");
  VC.setGallons(1);
  assertEqualFloat(1, VC.getGallons(), 0.0001);

  fprintf(stderr, "setQuarts\n");
  VC.setQuarts(1);
  assertEqualFloat(1, VC.getQuarts(), 0.0001);

  fprintf(stderr, "setPints\n");
  VC.setPints(1);
  assertEqualFloat(1, VC.getPints(), 0.0001);

  fprintf(stderr, "setCups\n");
  VC.setCups(1);
  assertEqualFloat(1, VC.getCups(), 0.0001);

  fprintf(stderr, "setFluidOunces\n");
  VC.setFluidOunces(1);
  assertEqualFloat(1, VC.getFluidOunces(), 0.0001);

  fprintf(stderr, "setTableSpoons\n");
  VC.setTableSpoons(1);
  assertEqualFloat(1, VC.getTableSpoons(), 0.0001);

  fprintf(stderr, "setTeaSpoons\n");
  VC.setTeaSpoons(1);
  assertEqualFloat(1, VC.getTeaSpoons(), 0.0001);
}


unittest(test_Gallons)
{
  VolumeConverter VC;

  VC.setGallons(1);
  assertEqualFloat(1, VC.getGallons(), 0.0001);
  assertEqualFloat(4, VC.getQuarts(), 0.0001);
  assertEqualFloat(8, VC.getPints(), 0.0001);
  assertEqualFloat(16, VC.getCups(), 0.0001);
  assertEqualFloat(128, VC.getFluidOunces(), 0.001);
  assertEqualFloat(256, VC.getTableSpoons(), 0.001);
  assertEqualFloat(768, VC.getTeaSpoons(), 0.003);
}



unittest_main()


//  -- END OF FILE --


