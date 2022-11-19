//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-04
// PURPOSE: unit tests for the ParallelPrinter library
//          https://github.com/RobTillaart/ParallelPrinter
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
#include "ParallelPrinter.h"


unittest_setup()
{
  fprintf(stderr, "PARALLELPRINTER_VERSION: %s\n", (char *) PARALLELPRINTER_VERSION);
}


unittest_teardown()
{
}


//  minimal
unittest(test_constructor_basic)
{
  ParallelPrinter PP;

  PP.begin();
  assertEqual(80, PP.getLineLength());
  assertEqual(60, PP.getPageLength());
  assertEqual(0, PP.getLineNumber());
  assertEqual(0, PP.getPageNumber());
  assertEqual(0, PP.getPosition());
  assertEqual(2, PP.getTabSize());
  assertEqual(1, PP.getLineFeed());

  PP.formfeed();
  PP.formfeed();
  PP.formfeed();
  PP.formfeed();
  PP.println("This is a test");
  PP.println("This is a test");
  PP.println("This is a test");
  PP.print("Hello World");

  // fprintf(stderr, "%d\n", PP.getLineNumber());
  // fprintf(stderr, "%d\n", PP.getPageNumber());
  // fprintf(stderr, "%d\n", PP.getPosition());

  assertEqual(3, PP.getLineNumber());  //  0 based
  assertEqual(4, PP.getPageNumber());  //  0 based
  assertEqual(11, PP.getPosition());   //  0 based
}


unittest(test_tabs_linefeed)
{
  ParallelPrinter PP;

  for (int tab = 0; tab < 10; tab +=2 )
  {
    fprintf(stderr, "%d\t", tab);
    PP.setTabSize(tab);
    assertEqual(tab, PP.getTabSize());
  }


  fprintf(stderr, "0\t");
  PP.setLineFeed(0);
  assertEqual(1, PP.getLineFeed());   //  minimum LF size

  for (int LF = 1; LF < 4; LF +=2 )
  {
    fprintf(stderr, "%d\t", LF);
    PP.setLineFeed(LF);
    assertEqual(LF, PP.getLineFeed());
  }
}


unittest(test_OutOfPaper)
{
  GodmodeState* state = GODMODE();
  state->reset();

  ParallelPrinter PP;

  // TODO
  // state->digitalPin[12] = 0;
  // assertFalse(PP.isOutOfPaper());
  //
  // state->digitalPin[12] = 1;
  // assertTrue(PP.isOutOfPaper());
}


unittest_main()

// --------
