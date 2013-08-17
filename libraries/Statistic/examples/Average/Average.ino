//
//    FILE: Average.ino
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.2
// PURPOSE: Sample sketch for statistic library Arduino
//

#include "Statistic.h"

Statistic myStats;

void setup(void)
{
  Serial.begin(9600);
  Serial.print("Demo Statistics lib ");
  Serial.print(STATISTIC_LIB_VERSION);
  myStats.clear(); //explicitly start clean
}

void loop(void)
{
  long rn = random(0, 9999);
  myStats.add(rn/100.0 + 1);
  if (myStats.count() == 10000)
  {
    Serial.print("  Count: ");
    Serial.println(myStats.count());
    Serial.print("  Min: ");
    Serial.println(myStats.minimum(),4);
    Serial.print("  Max: ");
    Serial.println(myStats.maximum(),4);
    Serial.print("  Average: ");
    Serial.println(myStats.average(), 4);
    // uncomment in Statistic.h file to use stdev
    #ifdef STAT_USE_STDEV
    Serial.print("    pop stdev: ");
    Serial.println(myStats.pop_stdev(), 4);
    Serial.print("  unbias stdev: ");
    Serial.println(myStats.unbiased_stdev(), 4);
    #endif
    Serial.println("=====================================");
    myStats.clear();
    delay(1000);
  }
}