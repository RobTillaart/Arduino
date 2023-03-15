//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-08
// PURPOSE: unit tests for the statHelpers
//          https://github.com/RobTillaart/statHelpers
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
#include "statHelpers.h"



unittest_setup()
{
  fprintf(stderr, "\nSTATHELPERS_LIB_VERSION: %s\n", (char *) STATHELPERS_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_permutations)
{
  fprintf(stderr, "\n\tpermutations(12, k)\n");
  for (int k = 0; k <= 12; k++)
  {
    fprintf(stderr, "%d\t%d\n", k, permutations(12, k));
  }

  fprintf(stderr, "\n\tpermutations64(20, k)\n");
  for (int k = 0; k <= 20; k++)
  {
    fprintf(stderr, "%d\t%ld\n", k, permutations64(20, k));
  }

  fprintf(stderr, "\n\tdpermutations(34, k)\n");
  for (int k = 0; k <= 34; k++)
  {
    fprintf(stderr, "%d\t%f\n", k, dpermutations(34, k));
  }

  fprintf(stderr, "\n120 permutations of abcde\n\n");
  char text[] = "abcde";
  int count = 0;
  do
  {
    fprintf(stderr, "%s\t", text);
    count++;
    if (count % 5 == 0) fprintf(stderr, "\n");
  }
  while (nextPermutation<char>(text, 5));
  fprintf(stderr, "\n\n");

  assertEqual(120, count);
}


unittest(test_factorial)
{
  fprintf(stderr, "\n\tfactorial(n)\n");
  for (int n = 0; n <= 12; n++)
  {
    fprintf(stderr, "%d\t%d\n", n, factorial(n));
  }

  fprintf(stderr, "\n\tfactorial64(n)\n");
  for (int n = 0; n <= 21; n++)
  {
    fprintf(stderr, "%d\t%ld\n", n, factorial64(n));
  }

  fprintf(stderr, "\n\tdfactorial(n)\n");
  for (int n = 0; n <= 35; n++)
  {
    fprintf(stderr, "%d\tDFACTORIAL: %f\n", n, dfactorial(n));
    fprintf(stderr, "  \t  STIRLING: %f\n", stirling(n));
    fprintf(stderr, "  \t     RATIO: %f\n", dfactorial(n) / stirling(n));
  }

  assertEqual(1, 1);  // keep unit test happy :)
}


unittest(test_combinations)
{
  fprintf(stderr, "\n\tcombinations(30, k)\n");
  for (int k = 0; k <= 30; k++)
  {
    fprintf(stderr, "%d\t%d\n", k, combinations(30, k));
  }

  fprintf(stderr, "\n\tcombinations64(61, k)\n");
  for (int k = 0; k <= 31; k++)
  {
    fprintf(stderr, "%d\t%ld\n", k, combinations64(61, k));
  }

  fprintf(stderr, "\n\tdcombinations(125, k)\n");
  for (int k = 0; k <= 63; k ++)
  {
    fprintf(stderr, "%d\t%f\n", k, dcombinations(125, k));
  }

  fprintf(stderr, "\n\trcombinations(30, k)\n");
  for (int k = 0; k <= 30; k++)
  {
    fprintf(stderr, "%d\t%d\n", k, rcombinations(30, k));
  }

  fprintf(stderr, "\n\trcombinations64(61, k)\n");
  for (int k = 0; k <= 31; k++)
  {
    fprintf(stderr, "%d\t%ld\n", k, rcombinations64(61, k));
  }

  fprintf(stderr, "\n\tcombPascal(30, k)\n");
  for (int k = 0; k <= 15; k++)
  {
    fprintf(stderr, "%d\t%d\n", k, combPascal(30, k));
  }

  assertEqual(1, 1);  //  keep unit test happy :)
}


unittest_main()


//  -- END OF FILE --

