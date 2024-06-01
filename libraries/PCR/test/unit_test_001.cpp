//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-05-30
// PURPOSE: unit tests for the PCR library
//     URL: https://github.com/RobTillaart/PCR
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


#include "PCR.h"


unittest_setup()
{
  fprintf(stderr, "PCR_LIB_VERSION: %s\n", (char *) PCR_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(PCR_STATE_IDLE      , 0);
  assertEqual(PCR_STATE_INITIAL   , 1);
  assertEqual(PCR_STATE_DENATURE  , 2);
  assertEqual(PCR_STATE_ANNEALING , 3);
  assertEqual(PCR_STATE_EXTENSION , 4);
  assertEqual(PCR_STATE_ELONGATION, 5);
  assertEqual(PCR_STATE_HOLD      , 6);
}


unittest(test_constructor_parameters)
{
  PCR pcr(8,9);

  pcr.setInitial(94, 50);
  assertEqualFloat(94, pcr.getInitialTemp(), 0.01);
  assertEqualFloat(50, pcr.getInitialTime(), 0.01);
  
  pcr.setDenature(93, 30);
  assertEqualFloat(93, pcr.getDenatureTemp(), 0.01);
  assertEqualFloat(30, pcr.getDenatureTime(), 0.01);
  
  pcr.setAnnealing(54, 40);
  assertEqualFloat(54, pcr.getAnnealingTemp(), 0.01);
  assertEqualFloat(40, pcr.getAnnealingTime(), 0.01);
  
  pcr.setExtension(75, 60);
  assertEqualFloat(75, pcr.getExtensionTemp(), 0.01);
  assertEqualFloat(60, pcr.getExtensionTime(), 0.01);
  
  pcr.setElongation(74, 90);
  assertEqualFloat(74, pcr.getElongationTemp(), 0.01);
  assertEqualFloat(90, pcr.getElongationTime(), 0.01);
  
  pcr.setHold(17);
  assertEqualFloat(17, pcr.getHoldTemp(), 0.01);
}


unittest(test_constructor_iterations)
{
  PCR pcr(8,9);

  assertEqual(0, pcr.iterationsLeft());
  for (int i = 1; i < 10; i++)
  {
    pcr.reset(i);
    assertEqual(i, pcr.iterationsLeft());
  }
}


unittest(test_constructor_heat_pulse_length)
{
  PCR pcr(8,9);

  assertEqual(10, pcr.getHeatPulseLength());
  for (int i = 10; i <= 100; i+= 10)
  {
    pcr.setHeatPulseLength(i);
    assertEqual(i, pcr.getHeatPulseLength());
  }
  //  test constrain
  pcr.setHeatPulseLength(5000);
  assertEqual(1000, pcr.getHeatPulseLength());

  pcr.setHeatPulseLength();
  assertEqual(10, pcr.getHeatPulseLength());

}


unittest(test_constructor_timeLeft)
{
  PCR pcr(8,9);

  assertEqualFloat(1, pcr.timeLeft(), 0.01);

  pcr.setInitial(94, 50);
  pcr.setDenature(93, 30);
  pcr.setAnnealing(54, 40);
  pcr.setExtension(75, 60);
  pcr.setElongation(74, 90);
  pcr.setHold(17);

  //  note: zero cycles
  assertEqualFloat(140, pcr.timeLeft(), 0.1);

  pcr.reset(10);
  assertEqualFloat(1440, pcr.timeLeft(), 0.1);
}


unittest_main()


//  -- END OF FILE --

