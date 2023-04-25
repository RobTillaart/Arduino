//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-12-01
// PURPOSE: unit tests for the A1301 magnetic sensor
//     URL: https://github.com/RobTillaart/A1301
//          https://www.adafruit.com/product/2857
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
#include "A1301.h"


unittest_setup()
{
    fprintf(stderr, "A1301_LIB_VERSION: %s\n", (char *) A1301_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqualFloat(1, 1, 0.001);
}


unittest(test_constructor)
{
  HALL  H(4);
  A1301 A(5);
  A1302 B(6);
  A1324 C(6);
  A1325 D(6);
  A1326 E(6);

  H.begin(3.3, 4095);
  A.begin(5.0, 1023);
  B.begin(5.0, 1023);
  C.begin(5.0, 1023);
  D.begin(5.0, 1023);
  E.begin(5.0, 1023);

  assertEqualFloat(2.500, H.getSensitivity(), 0.001);
  assertEqualFloat(2.500, A.getSensitivity(), 0.001);
  assertEqualFloat(1.300, B.getSensitivity(), 0.001);

  assertEqualFloat(5.000, C.getSensitivity(), 0.001);
  assertEqualFloat(3.125, D.getSensitivity(), 0.001);
  assertEqualFloat(2.500, E.getSensitivity(), 0.001);
}


unittest(test_midPoint)
{
  HALL  H(4);

  H.begin(3.3, 4095);
  H.setMidPoint(2020);
  assertEqualFloat(2020, H.getMidPoint(), 0.1);


  H.begin(2.5, 1000);
  assertEqualFloat(500, H.getMidPoint(), 0.1);


  H.begin(2.5, 1023);
  assertEqualFloat(511.5, H.getMidPoint(), 0.1);
}


unittest(test_sensitivity)
{
  HALL  H(4);

  H.begin(3.3, 4095);

  assertEqualFloat(2.500, H.getSensitivity(), 0.001);
  H.setSensitivity(2.480);
  assertEqualFloat(2.480, H.getSensitivity(), 0.001);
}


unittest(test_read_external_ADC)
{
  HALL  H(4);

  H.begin(3.3, 4095);
  H.setMidPoint(2047);

  assertEqualFloat(-0.337494, H.readExt(1000.0), 0.01);
  assertTrue(H.isSouth());

  assertEqualFloat(-0.176322, H.readExt(1500.0), 0.01);
  assertTrue(H.isSouth());

  assertEqualFloat(-0.0151502, H.readExt(2000.0), 0.01);
  assertTrue(H.isSouth());

  assertEqualFloat(0.307194, H.readExt(3000.0), 0.01);
  assertTrue(H.isNorth());
}


unittest(test_converters)
{
  HALL  H(4);

  H.begin(3.3, 4095);

  float Gauss = 50;

  assertEqualFloat(0.005, H.Tesla(Gauss), 0.01);
  assertEqualFloat(5.00, H.mTesla(Gauss), 0.01);
  assertEqualFloat(5000, H.uTesla(Gauss), 0.01);
}


unittest(test_maxGauss)
{
  HALL  H(4);

  H.begin(3.3, 4095);

  assertEqualFloat(500, H.getMaxGauss(), 0.1);
  H.setMaxGauss(400);
  assertEqualFloat(400, H.getMaxGauss(), 0.1);
}


unittest_main()


//  -- END OF FILE --

