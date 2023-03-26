//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-24
// PURPOSE: unit tests for the FunctionGenerator library
//          https://github.com/RobTillaart/FunctionGenerator
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
#include "functionGenerator.h"


unittest_setup()
{
  fprintf(stderr, "FUNCTIONGENERATOR_LIB_VERSION: %s\n", (char*) FUNCTIONGENERATOR_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  funcgen gen;

  fprintf(stderr, "Default values\n");
  assertEqualFloat(1, gen.getPeriod(), 0.0001);
  assertEqualFloat(1, gen.getFrequency(), 0.0001);
  assertEqualFloat(1, gen.getAmplitude(), 0.0001);

  assertEqualFloat(0, gen.getPhase(), 0.0001);
  assertEqualFloat(0, gen.getYShift(), 0.0001);
  assertEqualFloat(50, gen.getDutyCycle(), 0.0001);
}


unittest(test_constructor_param)
{
  funcgen gen(4, 2.5, 0.33, -0.5);

  fprintf(stderr, "funcgen gen(4, 2.5, 0.33, -0.5)\n");

  assertEqualFloat(4.00, gen.getPeriod(), 0.0001);
  assertEqualFloat(0.25, gen.getFrequency(), 0.0001);
  assertEqualFloat(2.50, gen.getAmplitude(), 0.0001);

  assertEqualFloat(0.33, gen.getPhase(), 0.0001);
  assertEqualFloat(-0.5, gen.getYShift(), 0.0001);
  assertEqualFloat(50,   gen.getDutyCycle(), 0.0001);
}


unittest(test_set_get_param)
{
  funcgen gen;

  fprintf(stderr, "set get parameters\n");

  gen.setPeriod(3.1415);
  assertEqualFloat(3.1415, gen.getPeriod(), 0.0001);

  gen.setFrequency(142.5);
  assertEqualFloat(142.5, gen.getFrequency(), 0.0001);

  gen.setAmplitude(2.345);
  assertEqualFloat(2.345, gen.getAmplitude(), 0.0001);

  gen.setPhase(1.5);
  assertEqualFloat(1.5, gen.getPhase(), 0.0001);

  gen.setYShift(6.89);
  assertEqualFloat(6.89, gen.getYShift(), 0.0001);

  gen.setDutyCycle(14.28);
  assertEqualFloat(14.28, gen.getDutyCycle(), 0.0001);
}


unittest(test_line_zero)
{
  funcgen gen;

  fprintf(stderr, "default line = 1.0 \n");

  assertEqualFloat(1.00, gen.line(), 0.0001);

  fprintf(stderr, "line = amplitude + yshift\n");

  gen.setAmplitude(2.34);
  gen.setYShift(6.89);
  assertEqualFloat(9.23, gen.line(), 0.0001);

  fprintf(stderr, "zero == 0 \n");

  assertEqual(0, gen.zero());
}


/*
  TODO wave forms 6x ?
*/


unittest_main()


//  -- END OF FILE --

