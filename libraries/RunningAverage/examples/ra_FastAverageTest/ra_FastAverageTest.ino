//
//    FILE: ra_FastAverageTest.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
//    DATE: 2015-sep-04
//
// PUPROSE: demo to see if different average algorithm give different result
//

#include "RunningAverage.h"

RunningAverage myRA(10);
uint32_t samples = 0;

double maxDiff = 0;

void setup(void)
{
  Serial.begin(115200);
  Serial.print("\nDemo ");
  Serial.println(__FILE__);
  Serial.print("Version: ");
  Serial.println(RUNNINGAVERAGE_LIB_VERSION);
  myRA.clear(); // explicitly start clean

  Serial.println("\nCNT\tAVG\tFASTAVG");
}

void loop(void)
{
  long rn = random(0, 1000);
  myRA.addValue(rn * 0.001);
  samples++;
  //
  double avg = myRA.getAverage();
  double favg = myRA.getFastAverage();
  double diff = abs(avg - favg);

  boolean pr = (samples % 10000 == 0);
  if (maxDiff < diff)
  {
    maxDiff = diff;
    pr = true;
  }

  if (pr)
  {
    Serial.print(samples);
    Serial.print("\t");
    Serial.print(avg, 7);
    Serial.print("\t");
    Serial.print(favg, 7);
    Serial.print("\t");
    Serial.print(diff, 7);
    Serial.print("\t");
    Serial.print(maxDiff, 7);
    Serial.println();
  }
}
