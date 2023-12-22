//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-01
// PURPOSE: unit tests for the MCP_POT
//          https://github.com/RobTillaart/MCP_POT
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
#include "MCP_POT.h"


unittest_setup()
{
  fprintf(stderr, "MCP_POT_LIB_VERSION: %s\n", (char *) MCP_POT_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(128, MCP_POT_MIDDLE_VALUE);
  assertEqual(255, MCP_POT_MAX_VALUE);
}


unittest(test_constructor)
{
  MCP_POT MCP1(9, 10, 11, 6, 7);  //  SW SPI
  MCP_POT MCP2(9, 10, 11, &SPI);  //  HW SPI

  MCP41010 MCP41_1(9, 10, 11, 6, 7);  //  SW SPI
  MCP41050 MCP41_2(9, 10, 11, 6, 7);  //  SW SPI
  MCP41100 MCP41_3(9, 10, 11, 6, 7);  //  SW SPI

  MCP42010 MCP42_1(9, 10, 11, &SPI);  //  HW SPI
  MCP42050 MCP42_2(9, 10, 11, &SPI);  //  HW SPI
  MCP42100 MCP42_3(9, 10, 11, &SPI);  //  HW SPI
  
  MCP1.begin();
  MCP2.begin();

  assertFalse(MCP1.usesHWSPI());
  assertTrue(MCP2.usesHWSPI());

  MCP41_1.begin();
  MCP41_2.begin();
  MCP41_3.begin();
  
  MCP42_1.begin();
  MCP42_2.begin();
  MCP42_3.begin();

  assertEqual(2, MCP1.pmCount());
  assertEqual(2, MCP2.pmCount());
  
  assertEqual(1, MCP41_1.pmCount());
  assertEqual(1, MCP41_1.pmCount());
  assertEqual(1, MCP41_1.pmCount());
  
  assertEqual(2, MCP42_1.pmCount());
  assertEqual(2, MCP42_2.pmCount());
  assertEqual(2, MCP42_3.pmCount());

  assertEqual(MCP_POT_MIDDLE_VALUE, MCP1.getValue());
  assertEqual(MCP_POT_MIDDLE_VALUE, MCP2.getValue());
  
  assertEqual(MCP_POT_MIDDLE_VALUE, MCP41_1.getValue());
  assertEqual(MCP_POT_MIDDLE_VALUE, MCP41_1.getValue());
  assertEqual(MCP_POT_MIDDLE_VALUE, MCP41_1.getValue());
  
  assertEqual(MCP_POT_MIDDLE_VALUE, MCP42_1.getValue());
  assertEqual(MCP_POT_MIDDLE_VALUE, MCP42_2.getValue());
  assertEqual(MCP_POT_MIDDLE_VALUE, MCP42_3.getValue());
}


unittest(test_setValue_both)
{
  MCP_POT MCP1(9, 10, 11, 6, 7);  //  SW SPI

  MCP1.begin();

  for (int i = 0; i < 256; i+= 33)
  {
    MCP1.setValue(i);
    assertEqual(i, MCP1.getValue(0));
    assertEqual(i, MCP1.getValue(1));
  }
}


unittest(test_setValue_0)
{
  MCP_POT MCP1(9, 10, 11, 6, 7);  //  SW SPI

  MCP1.begin();

  for (int i = 0; i < 256; i+= 33)
  {
    MCP1.setValue(0, i);
    assertEqual(i, MCP1.getValue(0));
    assertEqual(MCP_POT_MIDDLE_VALUE, MCP1.getValue(1));
  }
}


unittest(test_setValue_1)
{
  MCP_POT MCP1(9, 10, 11, 6, 7);  //  SW SPI

  MCP1.begin();

  for (int i = 0; i < 256; i+= 33)
  {
    MCP1.setValue(1, i);
    assertEqual(i, MCP1.getValue(1));
    assertEqual(MCP_POT_MIDDLE_VALUE, MCP1.getValue(0));
  }
}


unittest_main()


//  -- END OF FILE --
