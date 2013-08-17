//
//    FILE: fillValue.pde
//  AUTHOR: Rob Tillaart
//    DATE: 2012-12-30
//
// PUPROSE: show working of fillValue
//

#include "RunningAverage.h"

RunningAverage myRA(10);
int samples = 0;

void setup(void) 
{
  Serial.begin(115200);
  Serial.print("Demo RunningAverage lib - fillValue ");
  Serial.print("Version: ");
  Serial.println(RUNNINGAVERAGE_LIB_VERSION);
 
  myRA.fillValue(100,5);
}

void loop(void) 
{
  long rn = random(0, 100);
  myRA.addValue(rn/100.0);
  samples++;
  Serial.print("Running Average: ");
  Serial.println(myRA.getAverage(), 4);
  
  if (samples == 300)
  {
    samples = 0;
    myRA.fillValue(100, 10);
  }
  delay(100);
}