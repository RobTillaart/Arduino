//
//    FILE: fillValue.ino
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
  Serial.print("Demo RunningAverage lib - fillValue ");
  Serial.print("RUNNINGAVERAGE_LIB_VERSION: ");
  Serial.println(RUNNINGAVERAGE_LIB_VERSION);
  delay(10);

  for (int i = 0; i < 15; i++)
  {
	  measure_duration(i);
  }
  
  Serial.println();
}


void loop(void) 
{
  long rn = random(0, 100);
  myRA.addValue(rn / 100.0);
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


void measure_duration(int n)
{
  start = micros();
  myRA.fillValue(100, n);
  stop = micros();
  Serial.print("fillValue(100, ");
  Serial.print(n);
  Serial.print("): ");
  Serial.println(stop - start);
  delay(10);
}


//  -- END OF FILE --

