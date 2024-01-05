//
//    FILE: ra_MinMaxBufferTest.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2015-09-04
// PURPOSE: demo
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

  Serial.println("\nCNT\tMIN\tMINBUF\tMAX\tMAXBUF");
}


void loop(void)
{
  long rn = random(0, 1000);
  myRA.addValue(rn * 0.001);
  samples++;
  Serial.print(samples);
  Serial.print("\t");
  Serial.print(myRA.getMin(), 3);
  Serial.print("\t");
  Serial.print(myRA.getMinInBuffer(), 3);
  Serial.print("\t");
  Serial.print(myRA.getMaxInBuffer(), 3);
  Serial.print("\t");
  Serial.print(myRA.getMax(), 3);
  Serial.println();
  if (samples == 100)
  {
    samples = 0;
    myRA.clear();
    Serial.println("\nCNT\tMIN\tMINBUF\tMAX\tMAXBUF");
  }
  delay(10);
}


//  -- END OF FILE --

