//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-07-08
// PURPOSE: unit tests for the DRV8825 library
//          https://github.com/RobTillaart/DRV8825
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

#include "DRV8825.h"
#include "Wire.h"


unittest_setup()
{
  fprintf(stderr, "DRV8825_LIB_VERSION: %s\n", (char *) DRV8825_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0, DRV8825_CLOCK_WISE);
  assertEqual(1, DRV8825_COUNTERCLOCK_WISE);
}


unittest(test_constructor)
{
  DRV8825 stepper;

  assertTrue(stepper.begin(4, 5));

  assertTrue(stepper.setDirection());
  assertEqual(DRV8825_CLOCK_WISE, stepper.getDirection());

  assertTrue(stepper.setDirection(DRV8825_COUNTERCLOCK_WISE));
  assertEqual(DRV8825_COUNTERCLOCK_WISE, stepper.getDirection());
}


unittest(test_steps_per_rotation)
{
  DRV8825 stepper;

  assertTrue(stepper.begin(4, 5));
  assertEqual(0, stepper.getStepsPerRotation());

  stepper.setStepsPerRotation(1600);
  assertEqual(1600, stepper.getStepsPerRotation());
}


unittest(test_step_1)
{
  DRV8825 stepper;

  assertTrue(stepper.begin(4, 5));
  stepper.setStepsPerRotation(1600);

  for (int i= 0; i < 10; i++)
  {
    stepper.step();
    delay(1);
  }
  assertEqual(10, stepper.getSteps());
  for (int i= 0; i < 10; i++)
  {
    stepper.step();
    delay(1);
  }
  assertEqual(20, stepper.getSteps());
  
  stepper.resetSteps(0);
  for (int i= 0; i < 10; i++)
  {
    stepper.step();
    delay(1);
  }
  assertEqual(10, stepper.getSteps());
}


unittest(test_step_2)
{
  DRV8825 stepper;

  assertTrue(stepper.begin(4, 5));
  stepper.setStepsPerRotation(0);

  for (int i= 0; i < 10; i++)
  {
    stepper.step();
    delay(1);
    assertEqual(0, stepper.getSteps());
  }
}


unittest(test_step_pulse_length)
{
  DRV8825 stepper;

  assertTrue(stepper.begin(4, 5));
  stepper.setStepPulseLength();
  assertEqual(2, stepper.getStepPulseLength());
  for (int i = 0; i < 20; i += 3)
  {
    stepper.setStepPulseLength(i);
    assertEqual(i, stepper.getStepPulseLength());
  }
}



unittest_main()

// --------
