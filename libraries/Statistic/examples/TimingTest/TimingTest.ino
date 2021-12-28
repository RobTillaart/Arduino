//
//    FILE: TimingTest.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: measure time difference for runtime stddev toggle.
//          add is 1024 milliseconds faster for 10K adds ==> ~ 100uSec per add faster.


#include "Statistic.h"

Statistic myStats;

uint32_t start;
uint32_t stop;

bool useStdDev = true;


void setup(void)
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("Demo Statistics lib ");
  Serial.println(STATISTIC_LIB_VERSION);
  myStats.clear(useStdDev);
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
    if (useStdDev)
    {
      Serial.print("     variance: ");
      Serial.println(myStats.variance(), 4);
      Serial.print("    pop stdev: ");
      Serial.println(myStats.pop_stdev(), 4);
      Serial.print(" unbias stdev: ");
      Serial.println(myStats.unbiased_stdev(), 4);
    }
    Serial.print("     time(ms): ");
    Serial.println(stop - start);
    Serial.println("=====================================");
    useStdDev = !useStdDev;
    myStats.clear(useStdDev);
    start = millis();
  }
}


// -- END OF FILE --

