//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-09-25
// PURPOSE: unit tests for an analogue UV sensor.
//          https://github.com/RobTillaart/AnalogUVSensor
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

#define A0      0

#include "Arduino.h"
#include "AnalogUVSensor.h"


unittest_setup()
{
  fprintf(stderr, "ANALOG_UVSENSOR_LIB_VERSION: %s\n",  (char *) ANALOG_UVSENSOR_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(constructor)
{
  AnalogUVSensor AUV;

  AUV.begin(A0);
  fprintf(stderr, "UV: %f\n", AUV.read());

  assertEqualFloat(0.000000, AUV.read(), 0.01);
}


unittest(mv2index)
{
  AnalogUVSensor AUV;

  AUV.begin(A0);
  float uvi;
  for (uint16_t milliVolt = 0; milliVolt < 1200; milliVolt += 50)
  {
    uvi = AUV.mV2index(milliVolt);
    fprintf(stderr, "%d\t %f\n", milliVolt, uvi);
  }

  assertEqualFloat(0.000000, AUV.mV2index(0),    0.01);
  assertEqualFloat(0.000000, AUV.mV2index(50),   0.01);
  assertEqualFloat(0.282486, AUV.mV2index(100),  0.01);
  assertEqualFloat(0.847458, AUV.mV2index(200),  0.01);
  assertEqualFloat(1.856804, AUV.mV2index(300),  0.01);
  assertEqualFloat(2.905457, AUV.mV2index(400),  0.01);
  assertEqualFloat(3.954111, AUV.mV2index(500),  0.01);
  assertEqualFloat(5.002764, AUV.mV2index(600),  0.01);
  assertEqualFloat(6.051417, AUV.mV2index(700),  0.01);
  assertEqualFloat(7.100070, AUV.mV2index(800),  0.01);
  assertEqualFloat(8.148723, AUV.mV2index(900),  0.01);
  assertEqualFloat(9.197376, AUV.mV2index(1000), 0.01);
  assertEqualFloat(10.24602, AUV.mV2index(1100), 0.01);
}


unittest(index2color)
{
  AnalogUVSensor AUV;

  AUV.begin(A0);

  assertEqual('G', AUV.index2color(0));
  assertEqual('G', AUV.index2color(1));
  assertEqual('G', AUV.index2color(2));
  assertEqual('Y', AUV.index2color(3));
  assertEqual('Y', AUV.index2color(4));
  assertEqual('Y', AUV.index2color(5));
  assertEqual('O', AUV.index2color(6));
  assertEqual('O', AUV.index2color(7));
  assertEqual('R', AUV.index2color(8));
  assertEqual('R', AUV.index2color(9));
  assertEqual('R', AUV.index2color(10));
  assertEqual('P', AUV.index2color(11));
}



unittest_main()


//  -- END OF FILE --
