//
//    FILE: runningAverageHour.pde
//  AUTHOR: Rob Tillaart
//    DATE: 2012-12-30
//
// PUPROSE: show working of runningAverage per hour 
//          in 2 steps - last minute + last hour
//          3 or more steps also possible
//

#include "RunningAverage.h"

RunningAverage raMinute(60);
RunningAverage raHour(60);

int samples = 0;

void setup(void) 
{
  Serial.begin(115200);
  Serial.println("Demo RunningAverage lib - average per minute & hour");
  Serial.print("Version: ");
  Serial.println(RUNNINGAVERAGE_LIB_VERSION);
  raHour.clear();
  raMinute.clear();
}

void loop(void) 
{
  long rn = random(0, 100);
  raMinute.addValue(rn);
  samples++;
  
  if (samples % 60 == 0) raHour.addValue(raMinute.getAverage());
  
  Serial.print("  raMinute: ");
  Serial.print(raMinute.getAverage(), 4);
  Serial.print("  raHour: ");
  Serial.println(raHour.getAverage(), 4);
}