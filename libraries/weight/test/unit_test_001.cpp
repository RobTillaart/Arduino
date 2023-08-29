//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-09
// PURPOSE: unit tests for the weight conversion functions
//          https://github.com/RobTillaart/weight
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
#include "weight.h"



unittest_setup()
{
  fprintf(stderr, "WEIGHT_LIB_VERSION: %s\n", (char *) WEIGHT_LIB_VERSION);
}


unittest_teardown()
{
  fprintf(stderr, "\n");
}


unittest(test_lbs2kilo)
{
  for (int i = 0; i < 10; i++)
  {
    float val = random(10000) * 0.01;
    assertEqualFloat(val, lbs2kilo(kilo2lbs(val)), 0.0001);
  }
}


unittest(test_ounce2gram)
{
  for (int i = 0; i < 10; i++)
  {
    float val = random(10000) * 0.01;
    assertEqualFloat(val, ounce2gram(gram2ounce(val)), 0.0001);
  }
}


unittest(test_gram2kilo)
{
  for (int i = 0; i < 10; i++)
  {
    float val = random(10000) * 0.01;
    assertEqualFloat(val, gram2kilo(kilo2gram(val)), 0.0001);
  }
}


unittest(test_lbs2ounce)
{
  for (int i = 0; i < 10; i++)
  {
    float val = random(10000) * 0.01;
    assertEqualFloat(val, lbs2ounce(ounce2lbs(val)), 0.0001);
  }
}


unittest(test_stone2lbs)
{
  for (int i = 0; i < 10; i++)
  {
    float val = random(10000) * 0.01;
    assertEqualFloat(val, stone2lbs(lbs2stone(val)), 0.0001);
  }
}


unittest(test_stone2kilo)
{
  for (int i = 0; i < 10; i++)
  {
    float val = random(10000) * 0.01;
    assertEqualFloat(val, stone2kilo(kilo2stone(val)), 0.0001);
  }
}


unittest(test_US2metric)
{
  for (int i = 0; i < 10; i++)
  {
    float stone = random(10);
    float lbs   = random(10);
    float ounce = random(10);
    float kilo  = US2metric(stone, lbs, ounce);
    float val   = kilo2lbs(kilo);    
    assertEqualFloat(val, metric2US(kilo, stone, lbs, ounce), 0.0001);
    fprintf(stderr, "\t\t%f kilo = ", kilo);
    fprintf(stderr, "%f stone + ", stone);
    fprintf(stderr, "%f lbs + ", lbs);
    fprintf(stderr, "%f ounce\n", ounce);
  }
}


unittest(test_weightConverter)
{
  weightConverter WC;
  
  fprintf(stderr, "setKilogram\n");
  WC.setKilogram(1);
  assertEqualFloat(1, WC.getKilogram(), 0.0001);
  
  fprintf(stderr, "setGram\n");
  WC.setGram(1);
  assertEqualFloat(1, WC.getGram(), 0.0001);
  
  fprintf(stderr, "setLBS\n");
  WC.setLBS(1);
  assertEqualFloat(1, WC.getLBS(), 0.0001);
  
  fprintf(stderr, "setStone\n");
  WC.setStone(1);
  assertEqualFloat(1, WC.getStone(), 0.0001);
  
  fprintf(stderr, "setOunce\n");
  WC.setOunce(1);
  assertEqualFloat(1, WC.getOunce(), 0.0001);
  
  fprintf(stderr, "setLongTonUK\n");
  WC.setLongTonUK(1);
  assertEqualFloat(1, WC.getLongTonUK(), 0.0001);
  
  fprintf(stderr, "setShortTonUS\n");
  WC.setShortTonUS(1);
  assertEqualFloat(1, WC.getShortTonUS(), 0.0001);
  
  fprintf(stderr, "setQuarterUK\n");
  WC.setQuarterUK(1);
  assertEqualFloat(1, WC.getQuarterUK(), 0.0001);
  
  fprintf(stderr, "setQuarterUS\n");
  WC.setQuarterUS(1);
  assertEqualFloat(1, WC.getQuarterUS(), 0.0001);
  
  fprintf(stderr, "setSlug\n");
  WC.setSlug(1);
  assertEqualFloat(1, WC.getSlug(), 0.0001);
  
  fprintf(stderr, "setTroyPound\n");
  WC.setTroyPound(1);
  assertEqualFloat(1, WC.getTroyPound(), 0.0001);
  
  fprintf(stderr, "setTroyOunce\n");
  WC.setTroyOunce(1);
  assertEqualFloat(1, WC.getTroyOunce(), 0.0001);
  
  fprintf(stderr, "setRobie\n");
  WC.setRobie(1);
  assertEqualFloat(1, WC.getRobie(), 0.0001);
  
  fprintf(stderr, "setDram\n");
  WC.setDram(1);
  assertEqualFloat(1, WC.getDram(), 0.0001);
  
  fprintf(stderr, "setDrachme\n");
  WC.setDrachme(1);
  assertEqualFloat(1, WC.getDrachme(), 0.0001);
  
  fprintf(stderr, "setPoint\n");
  WC.setPoint(1);
  assertEqualFloat(1, WC.getPoint(), 0.0001);
  
  fprintf(stderr, "setGrain\n");
  WC.setGrain(1);
  assertEqualFloat(1, WC.getGrain(), 0.0001);
  
  fprintf(stderr, "setCarat\n");
  WC.setCarat(1);
  assertEqualFloat(1, WC.getCarat(), 0.0001);
}


unittest_main()


//  -- END OF FILE --

