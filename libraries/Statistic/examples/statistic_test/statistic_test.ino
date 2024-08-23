//
//    FILE: statistic_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test sketch


#include "Statistic.h"

statistic::Statistic<float, uint32_t, true> myStats;
// Statistic myStats;  // pre 1.0.0 declaration


void setup(void)
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("Demo Statistics lib ");
  Serial.println(STATISTIC_LIB_VERSION);

  myStats.clear();  //  explicitly start clean


  for (int i = 0; i < 10; i++)
  {
    myStats.add(i * 0.01 + 1);  //  add 10 elements
  }
  Serial.print("        Count: ");
  Serial.println(myStats.count());
  Serial.print("          Min: ");
  Serial.println(myStats.minimum(), 4);
  Serial.print("          Max: ");
  Serial.println(myStats.maximum(), 4);
  Serial.print("      Average: ");
  Serial.println(myStats.average(), 4);
  Serial.print("     variance: ");
  Serial.println(myStats.variance(), 4);
  Serial.print("    pop stdev: ");
  Serial.println(myStats.pop_stdev(), 4);
  Serial.print(" unbias stdev: ");
  Serial.println(myStats.unbiased_stdev(), 4);
  Serial.print("CoefVariation: ");
  Serial.println(myStats.getCoefficientOfVariation(), 4);
}


void loop(void)
{
}


//  -- END OF FILE --
