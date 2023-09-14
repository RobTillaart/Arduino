//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-09-13
// PURPOSE: unit tests for the PulseDIvider
//          https://github.com/RobTillaart/PulseDivider
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
#include "PulseDivider.h"


unittest_setup()
{
    fprintf(stderr, "PULSEDIVIDER_LIB_VERSION: %s\n", (char *) PULSEDIVIDER_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  PulseDivider PDiv(5, 6, 8, 1, 2, FALLING, true);  //  all set explicit.

  fprintf(stderr, "IN   \t%d\n", PDiv.getInPin());
  fprintf(stderr, "OUT  \t%d\n", PDiv.getOutPin());
  fprintf(stderr, "RATIO\t%f\n", PDiv.getRatio());
  fprintf(stderr, "DUR  \t%d\n", PDiv.getDuration());
  fprintf(stderr, "EDGE \t%d\n", PDiv.getEdge());
  fprintf(stderr, "INV  \t%d\n", PDiv.getInvert());

  assertEqual(5,       PDiv.getInPin());
  assertEqual(6,       PDiv.getOutPin());
  assertEqualFloat(8,  PDiv.getRatio(), 0.001);
  assertEqual(2,       PDiv.getDuration());
  assertEqual(FALLING, PDiv.getEdge());
  assertTrue(PDiv.getInvert());


  PulseDivider PDiv1(5, 6, 17, 3);
  assertEqual(5,       PDiv1.getInPin());
  assertEqual(6,       PDiv1.getOutPin());
  assertEqualFloat(5.666666, PDiv1.getRatio(), 0.001);
  assertEqual(1,       PDiv1.getDuration());
  assertEqual(RISING,  PDiv1.getEdge());
  assertFalse(PDiv1.getInvert());
}



unittest_main()


//  -- END OF FILE --
