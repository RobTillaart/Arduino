//
//    FILE: ra_getAverageSubset.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2012-12-30
// PURPOSE: show working of runningAverage
//     URL: https://github.com/RobTillaart/RunningAverage


#include "RunningAverage.h"


RunningAverage myRA(10);
int samples = 0;


void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RUNNINGAVERAGE_LIB_VERSION: ");
  Serial.println(RUNNINGAVERAGE_LIB_VERSION);

  myRA.clear();  //  explicitly start clean

  for (int i = 0; i < 20; i++)
  {
    myRA.addValue(i);
  }
  Serial.println();
  Serial.print(myRA.getAverage(), 3);
  Serial.print("\t");
  Serial.print(myRA.getAverageSubset(0, 5), 3);
  Serial.print("\t");
  Serial.print(myRA.getAverageSubset(3, 5), 3);
  Serial.print("\t");
  Serial.println(myRA.getAverageSubset(5, 5), 3);
  Serial.println();
  delay(10000);

  myRA.clear();  //  explicitly start clean
}


void loop(void)
{
  long rn = random(0, 1000);
  myRA.addValue(rn * 0.001);
  samples++;
  Serial.print(samples);
  Serial.print("\t");
  Serial.print(100 * myRA.getAverage(), 3);
  Serial.print("\t");
  Serial.println(100 * myRA.getAverageSubset(5, 5), 3);

  if (samples == 300)
  {
    samples = 0;
    myRA.clear();
    Serial.println();
  }
  delay(10);
}


//  -- END OF FILE --
