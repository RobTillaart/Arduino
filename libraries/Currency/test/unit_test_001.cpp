//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-02-27
// PURPOSE: unit tests for the printHelpers
//          https://github.com/RobTillaart/currency
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
#include "currency.h"


unittest_setup()
{
  fprintf(stderr, "CURRENCY_VERSION: %s\n", (char *) CURRENCY_VERSION);
}


unittest_teardown()
{
}


unittest(currency32)
{
  fprintf(stderr, "%s\n", currency(10000000, 0, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(10000000, 1, '.', ',', 'E') );
  fprintf(stderr, "%s\n", currency(10000000, 2, '.', ',', 'Y') );
  fprintf(stderr, "%s\n", currency(10000000, 3, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(10000000, 4, '.', ',', '$') );
  fprintf(stderr, "\n");

  fprintf(stderr, "%s\n", currency(0, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(9, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(10, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(99, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(100, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(999, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(1000, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(9999, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(10000, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(99999, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(100000, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(999999, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(1000000, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(9999999, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(10000000, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(99999999, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(100000000, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(999999999, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(1000000000, 2, '.', ',', '$') );
  fprintf(stderr, "\n");

  fprintf(stderr, "%s\n", currency(-0, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(-9, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(-10, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(-99, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(-100, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(-999, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(-1000, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(-9999, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(-10000, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(-99999, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(-100000, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(-999999, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(-1000000, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(-9999999, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(-10000000, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(-99999999, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(-100000000, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(-999999999, 2, '.', ',', '$') );
  fprintf(stderr, "%s\n", currency(-1000000000, 2, '.', ',', '$') );
  fprintf(stderr, "\n");

  assertEqual(0, strcmp("$ 0.00",         currency(0, 2, '.', ',', '$') ) );
  assertEqual(0, strcmp("$ 9,999,999.99", currency(999999999, 2, '.', ',', '$') ) );
  assertEqual(0, strcmp("$-9,999,999.99", currency(-999999999, 2, '.', ',', '$') ) );
}


unittest(currency64)
{
  assertEqual(0, strcmp("$ 0.00",         currency64(0, 2, '.', ',', '$') ) );
  assertEqual(0, strcmp("$ 9,999,999.99", currency64(999999999, 2, '.', ',', '$') ) );
  assertEqual(0, strcmp("$-9,999,999.99", currency64(-999999999, 2, '.', ',', '$') ) );
}


unittest(wrappers32)
{
  assertEqual(0, strcmp("$ 0.00",         dollar(0) ) );
  assertEqual(0, strcmp("$ 9,999,999.99", dollar(999999999) ) );
  assertEqual(0, strcmp("$-9,999,999.99", dollar(-999999999) ) );
  assertEqual(0, strcmp("E 9.999.999,99", euro(999999999) ) );
  assertEqual(0, strcmp("E-9.999.999,99", euro(-999999999) ) );
  assertEqual(0, strcmp("B 999.999999",   bitcoin(999999999) ) );
  assertEqual(0, strcmp("B-999.999999",   bitcoin(-999999999) ) );
}


unittest(wrappers64)
{
  assertEqual(0, strcmp("$ 0.00",         dollar64(0) ) );
  assertEqual(0, strcmp("$ 9,999,999.99", dollar64(999999999) ) );
  assertEqual(0, strcmp("$-9,999,999.99", dollar64(-999999999) ) );
  assertEqual(0, strcmp("E 9.999.999,99", euro64(999999999) ) );
  assertEqual(0, strcmp("E-9.999.999,99", euro64(-999999999) ) );
  assertEqual(0, strcmp("B 999.999999",   bitcoin64(999999999) ) );
  assertEqual(0, strcmp("B-999.999999",   bitcoin64(-999999999) ) );
}

unittest(wrappersdouble)
{
  assertEqual(0, strcmp("$ 0.00",     dollarf(0) ) );
  assertEqual(0, strcmp("$ 9,999.99", dollarf(9999.99) ) );
  assertEqual(0, strcmp("$-9,999.99", dollarf(-9999.99) ) );
  assertEqual(0, strcmp("E 9.999,99", eurof(9999.99) ) );
  assertEqual(0, strcmp("E-9.999,99", eurof(-9999.99) ) );
  // rounding !!
  fprintf(stderr, "%s\n", bitcoinf(9999.99) );
  fprintf(stderr, "%s\n", bitcoinf(-9999.99) );

  assertEqual(0, strcmp("B 9,999.990000", bitcoinf(9999.99) ) );
  assertEqual(0, strcmp("B-9,999.990000", bitcoinf(-9999.99) ) );
}


unittest_main()

// --------
