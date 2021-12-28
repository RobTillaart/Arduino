//
//    FILE: StatisticArray.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Sample sketch for statistic library Arduino


#include "Statistic.h"

Statistic stats[4];


void setup(void)
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("Demo Statistics lib ");
  Serial.println(STATISTIC_LIB_VERSION);
  for (int i=0; i<4; i++)
  {
    stats[i].clear(); //explicitly start clean
  }
}


void loop(void)
{
  long rn = random(0, 9999);
  int idx = random(0, 4);
  stats[idx].add(rn / 100.0 + 1);
  
  if (stats[idx].count() == 10000)
  {
    Serial.print("IDX: ");
    Serial.println(idx);
    Serial.print("        Count: ");
    Serial.println(stats[idx].count());
    Serial.print("          Min: ");
    Serial.println(stats[idx].minimum(), 4);
    Serial.print("          Max: ");
    Serial.println(stats[idx].maximum(), 4);
    Serial.print("      Average: ");
    Serial.println(stats[idx].average(), 4);
    Serial.println("=====================================");
    stats[idx].clear();
  }
}


// -- END OF FILE --

