//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the BH1750FVI_RT (GY-30) lux sensor library
//          https://github.com/RobTillaart/BH1750FVI_RT
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

#include "BH1750FVI.h"


unittest_setup()
{
  fprintf(stderr, "BH1750FVI_LIB_VERSION: %s\n", (char *) BH1750FVI_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  BH1750FVI myLux(0x23);

  Wire.begin();
  myLux.begin();

  myLux.setContHigh2Res();
  assertEqual(2, myLux.getMode());
  myLux.setContHighRes();
  assertEqual(1, myLux.getMode());
  myLux.setContLowRes();
  assertEqual(0, myLux.getMode());

  assertFalse(myLux.isReady());

  myLux.setOnceHigh2Res();
  assertEqual(2, myLux.getMode());
  myLux.setOnceHighRes();
  assertEqual(1, myLux.getMode());
  myLux.setOnceLowRes();
  assertEqual(0, myLux.getMode());

  assertFalse(myLux.isReady());
}


unittest(test_constants)
{
  assertEqual(0x23, BH1750FVI_DEFAULT_ADDRESS);
  assertEqual(0x5C, BH1750FVI_ALT_ADDRESS);

  assertEqual(0x45, BH1750FVI_REFERENCE_TIME);

  assertEqual(0x00, BH1750FVI_MODE_LOW);
  assertEqual(0x01, BH1750FVI_MODE_HIGH);
  assertEqual(0x02, BH1750FVI_MODE_HIGH2);
  
  assertEqual(   0, BH1750FVI_OK);
  assertEqual( -10, BH1750FVI_ERROR_WIRE_REQUEST);
}


unittest(test_read)
{
  BH1750FVI myLux(0x23);

  Wire.begin();
  myLux.begin();

  assertEqual(0, myLux.getError());
  assertEqual(0, myLux.getRaw());
  assertEqual(0, myLux.getLux());
}


unittest(test_parameters)
{
  BH1750FVI myLux(0x23);

  Wire.begin();
  myLux.begin();

  //  0.45 .. 3.68
  myLux.setCorrectionFactor(3.14);
  assertEqualFloat(3.14, myLux.getCorrectionFactor(), 0.01);

  //  -89 - 89
  myLux.setAngle(30);
  assertEqual(30, myLux.getAngle());

  // 
  myLux.setTemperature(42);
  assertEqual(42, myLux.getTemperature());

  //  400 - 715
  myLux.setWaveLength(700);
  assertEqual(700, myLux.getWaveLength());
}


unittest(test_correctionFactor)
{
  BH1750FVI myLux(0x23);

  Wire.begin();
  myLux.begin();

  //  0.45 .. 3.68
  assertEqual( 31, myLux.setCorrectionFactor(0.00) );
  assertEqual( 31, myLux.setCorrectionFactor(0.44) );
  assertEqual( 31, myLux.setCorrectionFactor(0.45) );
  assertEqual( 69, myLux.setCorrectionFactor(1.00) );
  assertEqual(254, myLux.setCorrectionFactor(3.68) );
  assertEqual(254, myLux.setCorrectionFactor(3.69) );
}


unittest(test_angleFactor)
{
  BH1750FVI myLux(0x23);

  Wire.begin();
  myLux.begin();

  //  -89 ..89
  assertEqualFloat(572.967,  myLux.setAngle(-90), 0.001);
  assertEqualFloat( 57.2987, myLux.setAngle(-89), 0.0001);
  assertEqualFloat( 2.00000, myLux.setAngle(-60), 0.0001);
  assertEqualFloat( 1.41421, myLux.setAngle(-45), 0.0001);
  assertEqualFloat( 1.15470, myLux.setAngle(-30), 0.0001);
  assertEqualFloat( 1.00000, myLux.setAngle(  0), 0.0001);
  assertEqualFloat( 1.15470, myLux.setAngle( 30), 0.0001);
  assertEqualFloat( 1.41421, myLux.setAngle( 45), 0.0001);
  assertEqualFloat( 2.00000, myLux.setAngle( 60), 0.0001);
  assertEqualFloat( 57.2987, myLux.setAngle( 89), 0.0001);
  assertEqualFloat( 572.967, myLux.setAngle( 90), 0.001);
}


unittest(test_temperatureFactor)
{
  BH1750FVI myLux(0x23);

  Wire.begin();
  myLux.begin();

  //  -20 .. 100
  assertEqualFloat(1.020, myLux.setTemperature(-20), 0.001);
  assertEqualFloat(1.015, myLux.setTemperature(-10), 0.001);
  assertEqualFloat(1.010, myLux.setTemperature(  0), 0.001);
  assertEqualFloat(1.005, myLux.setTemperature( 10), 0.001);
  assertEqualFloat(1.000, myLux.setTemperature( 20), 0.001);
  assertEqualFloat(0.995, myLux.setTemperature( 30), 0.001);
  assertEqualFloat(0.990, myLux.setTemperature( 40), 0.001);
  assertEqualFloat(0.985, myLux.setTemperature( 50), 0.001);
  assertEqualFloat(0.980, myLux.setTemperature( 60), 0.001);
  assertEqualFloat(0.975, myLux.setTemperature( 70), 0.001);
  assertEqualFloat(0.970, myLux.setTemperature( 80), 0.001);
  assertEqualFloat(0.965, myLux.setTemperature( 90), 0.001);
  assertEqualFloat(0.960, myLux.setTemperature(100), 0.001);
}


unittest(test_wavelengthFactor)
{
  BH1750FVI myLux(0x23);

  Wire.begin();
  myLux.begin();

  //  400 - 715
  assertEqualFloat(100.000, myLux.setWaveLength(300), 0.001);
  assertEqualFloat(100.000, myLux.setWaveLength(400), 0.001);
  assertEqualFloat(4.66667, myLux.setWaveLength(450), 0.0001);
  assertEqualFloat(1.27273, myLux.setWaveLength(500), 0.0001);
  assertEqualFloat(1.20690, myLux.setWaveLength(550), 0.0001);
  assertEqualFloat(1.00000, myLux.setWaveLength(580), 0.0001);
  assertEqualFloat(1.18343, myLux.setWaveLength(600), 0.0001);
  assertEqualFloat(2.18579, myLux.setWaveLength(650), 0.0001);
  assertEqualFloat(14.2857, myLux.setWaveLength(700), 0.0001);
  assertEqualFloat(100.000, myLux.setWaveLength(715), 0.001);
  assertEqualFloat(100.000, myLux.setWaveLength(750), 0.001);
}



unittest_main()


//  -- END OF FILE --
