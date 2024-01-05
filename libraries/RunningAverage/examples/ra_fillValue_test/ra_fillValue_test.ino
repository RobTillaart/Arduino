//
//    FILE: ra_fillValue_test.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2012-12-30
// PURPOSE: demo + timing of fillValue
//     URL: https://github.com/RobTillaart/RunningAverage


#include "RunningAverage.h"


RunningAverage myRA(10);
int samples = 0;

uint32_t start, stop;


void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RUNNINGAVERAGE_LIB_VERSION: ");
  Serial.println(RUNNINGAVERAGE_LIB_VERSION);
  delay(10);

  for (int i = 0; i < 15; i++)
  {
    measure_duration(i);
    check_statistics();
  }

  Serial.println();
}


void loop(void)
{
}


void measure_duration(int n)
{
  start = micros();
  myRA.fillValue(100, n);
  stop = micros();
  Serial.print("fillValue(100, ");
  Serial.print(n);
  Serial.print("): ");
  Serial.println(stop - start);
  delay(100);
}


void check_statistics()
{
  Serial.print(myRA.getAverage());
  Serial.print("\t");
  Serial.print(myRA.getFastAverage());
  Serial.print("\t");
  Serial.print(myRA.getSize());
  Serial.print("\t");
  Serial.print(myRA.getCount());
  Serial.print("\t");
  Serial.print(myRA.getMinInBuffer());
  Serial.print("\t");
  Serial.print(myRA.getMaxInBuffer());
  Serial.print("\t");
  Serial.print(myRA.getStandardDeviation());
  Serial.print("\n");
}


//  -- END OF FILE --
