//
//    FILE: Average.ino
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.3
// PURPOSE: Sample sketch for statistic library Arduino
//

#include "Statistic.h"

Statistic myStats;

uint32_t start;
uint32_t stop;

void setup(void)
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("Demo Statistics lib ");
  Serial.println(STATISTIC_LIB_VERSION);
  myStats.clear(); //explicitly start clean
  start = millis();
}

void loop(void)
{
  long rn = random(0, 9999);
  myStats.add(rn / 100.0 + 1);
  if (myStats.count() == 10000)
  {
    stop = millis();
    Serial.print("        Count: ");
    Serial.println(myStats.count());
    Serial.print("          Min: ");
    Serial.println(myStats.minimum(), 4);
    Serial.print("          Max: ");
    Serial.println(myStats.maximum(), 4);
    Serial.print("      Average: ");
    Serial.println(myStats.average(), 4);
    // uncomment in Statistic.h file to use stdev
#ifdef STAT_USE_STDEV
    Serial.print("     variance: ");
    Serial.println(myStats.variance(), 4);
    Serial.print("    pop stdev: ");
    Serial.println(myStats.pop_stdev(), 4);
    Serial.print(" unbias stdev: ");
    Serial.println(myStats.unbiased_stdev(), 4);
#endif
    Serial.print("     time(ms): ");
    Serial.println(stop - start);
    Serial.println("=====================================");
    myStats.clear();
    delay(1000);
    start = millis();
  }
}