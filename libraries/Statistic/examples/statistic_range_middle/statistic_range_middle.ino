//
//    FILE: statistic_range_middle.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Sample sketch for statistic library Arduino


#include "Statistic.h"

statistic::Statistic<float, uint32_t, true> myStats;
// Statistic myStats;  // pre 1.0.0 declaration


void setup(void)
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("STATISTIC_LIB_VERSION: ");
  Serial.println(STATISTIC_LIB_VERSION);
  myStats.clear();  //  explicitly start clean
}


void loop(void)
{
  long rn = random(0, 9999);
  myStats.add(rn / 100.0 + 1);
  if (myStats.count() == 10000)
  {
    Serial.print("        Count: ");
    Serial.println(myStats.count());
    Serial.print("          Min: ");
    Serial.println(myStats.minimum(), 4);
    Serial.print("          Max: ");
    Serial.println(myStats.maximum(), 4);
    Serial.print("        Range: ");
    Serial.println(myStats.range(), 4);
    Serial.print("       Middle: ");
    Serial.println(myStats.middle(), 4);
    Serial.print("      Average: ");
    Serial.println(myStats.average(), 4);
    Serial.print(" middle - avg: ");
    Serial.println(myStats.middle() - myStats.average(), 4);
    Serial.print("     variance: ");
    Serial.println(myStats.variance(), 4);
    Serial.print("    pop stdev: ");
    Serial.println(myStats.pop_stdev(), 4);
    Serial.print(" range/stddev: ");
    Serial.println(myStats.range() / myStats.pop_stdev(), 4);
    Serial.println("=====================================");
    myStats.clear();
    delay(1000);
  }
}


//  -- END OF FILE --
