//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-03-09
// PURPOSE: unit tests for the AtomicWeight library
//          https://github.com/RobTillaart/AtomicWeight
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


#include "AtomicWeight.h"


unittest_setup()
{
  fprintf(stderr, "ATOMIC_WEIGHT_LIB_VERSION: %s\n", (char *) ATOMIC_WEIGHT_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{

}


unittest(test_constructor)
{
  PTOE ptoe;
  
  assertEqual(118, ptoe.size());
}


unittest(test_find)
{
  PTOE ptoe;

  assertEqual( 0, ptoe.find("n"));
  assertEqual( 1, ptoe.find("H"));
  assertEqual( 6, ptoe.find("C"));
  assertEqual(10, ptoe.find("Ne"));
  assertEqual(18, ptoe.find("Ar"));
  assertEqual(26, ptoe.find("Fe"));
  assertEqual(36, ptoe.find("Kr"));
  assertEqual(47, ptoe.find("Ag"));
  assertEqual(54, ptoe.find("Xe"));
  assertEqual(79, ptoe.find("Au"));
  assertEqual(92, ptoe.find("U"));
  
  assertEqual(255, ptoe.find("XX"));  //  Fail test
}


unittest(test_basic_atom)
{
  PTOE ptoe;

  int el = 0;

  //  NEUTRONIUM
  assertEqual("n", ptoe.name(el));
  assertEqual(  0, ptoe.electrons(el));
  assertEqual(  1, ptoe.neutrons(el));
  assertEqual(  0, ptoe.protons(el));
  assertEqual(  1, round(ptoe.weight(el)));

  //  HYDROGEN
  el = 1;
  assertEqual("H", ptoe.name(el));
  assertEqual(  1, ptoe.electrons(el));
  assertEqual(  0, ptoe.neutrons(el));
  assertEqual(  1, ptoe.protons(el));
  assertEqual(  1, round(ptoe.weight(el)));

  //  URANIUM
  el = 92;
  assertEqual("U", ptoe.name(el));
  assertEqual( 92, ptoe.electrons(el));
  assertEqual(146, ptoe.neutrons(el));
  assertEqual( 92, ptoe.protons(el));
  assertEqual(238, round(ptoe.weight(el)));
}


unittest(test_weight_formula)
{
  PTOE ptoe;
  assertEqualFloat( 22.9914, ptoe.weight("Na"), 0.1);
  assertEqualFloat( 58.4454, ptoe.weight("NaCl"), 0.1);
  assertEqualFloat( 100.081, ptoe.weight("CaCO3"), 0.1);
  assertEqualFloat( 98.0759, ptoe.weight("H2SO4"), 0.1);
  assertEqualFloat( 116.065, ptoe.weight("C2H2(COOH)2"), 0.1);
  assertEqualFloat( 666.178, ptoe.weight("YBa2Cu3O7"), 0.1);
  assertEqualFloat( 72.1146, ptoe.weight("C(O(H2)2)3"), 0.1);
}



unittest_main()

// --------
