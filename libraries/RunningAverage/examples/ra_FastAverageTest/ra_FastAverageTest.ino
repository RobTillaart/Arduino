//
//    FILE: ra_FastAverageTest.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2015-sep-04
// PURPOSE: demo to see if different average algorithm give different result
//     URL: https://github.com/RobTillaart/RunningAverage


#include "RunningAverage.h"


RunningAverage myRA(16);

float avg = 0;
float favg = 0;
float diff = 0;
float maxDiff = 0;

uint32_t start, stop;


void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RUNNINGAVERAGE_LIB_VERSION: ");
  Serial.println(RUNNINGAVERAGE_LIB_VERSION);

  //  explicitly start clean
  myRA.clear();

  measure_duration();
}


void loop()
{
  test(1000000);
}


void measure_duration()
{
  myRA.fillValue(100, 16);
  start = micros();
  favg = myRA.getFastAverage();
  stop = micros();
  Serial.print("getFastAverage: ");
  Serial.println(stop - start);
  delay(10);

  myRA.fillValue(100, 16);
  start = micros();
  favg = myRA.getAverage();
  stop = micros();
  Serial.print("    getAverage: ");
  Serial.println(stop - start);
  delay(10);
  Serial.println();
}  


void test(long n)
{
  Serial.println("\nCNT\tAVG\t\tFASTAVG\t\tDIFF\t\tMAXDIFF");

  for (long i = 0; i < n; i++)
  {
    long rn = random(0, 1000);
    myRA.addValue(rn * 0.001);
    if ( i % 1000 == 0)
    {
      //  the order of the next two lines is important as getAverage() resets the _sum
      //  used by the getFastAverage();
      favg = myRA.getFastAverage();
      avg = myRA.getAverage();
      diff = abs(avg - favg);
      if (diff > maxDiff) maxDiff = diff;

      Serial.print(i);
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
  delay(100);
}


//  -- END OF FILE --

