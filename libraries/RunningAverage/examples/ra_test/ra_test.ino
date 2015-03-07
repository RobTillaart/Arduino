//
//    FILE: runningAverageTest.pde
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
//    DATE: 2012-12-30
//
// PUPROSE: show working of runningAverage
//

#include "RunningAverage.h"

RunningAverage myRA(10);
int samples = 0;

void setup(void) 
{
  Serial.begin(115200);
  Serial.println("Demo RunningAverage lib");
  Serial.print("Version: ");
  Serial.println(RUNNINGAVERAGE_LIB_VERSION);
  myRA.clear(); // explicitly start clean
}

void loop(void) 
{
  long rn = random(0, 1000);
  myRA.addValue(rn * 0.001);
  samples++;
  Serial.print(samples);
  Serial.print("\t Running Average: ");
  Serial.println(myRA.getAverage(), 3);
  
  if (samples == 300)
  {
    samples = 0;
    myRA.clear();
    Serial.println();
  }
  delay(10);
}