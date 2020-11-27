//
//    FILE: RunningMedianQuantileTest.ino
//  AUTHOR: f-s ( derived from Rob Tillaart )
// VERSION: 0.1.2
// PURPOSE: demo basic quantile usage
//    DATE: 2020-09-02
//     URL: https://github.com/RobTillaart/RunningMedian
//

#include <RunningMedian.h>

RunningMedian samples = RunningMedian(5);

void setup()
{
  Serial.begin(115200);
  Serial.print("Running Median Version: ");  
  Serial.println(RUNNING_MEDIAN_VERSION);
}

void loop()
{
  test1();
}

void test1()
{
  int x = analogRead(A0);
  
  samples.add(x);
  // calculate the 5% quantile => 0.05
  long q = samples.getQuantile(0.05);
  
  Serial.print(millis());
  Serial.print("\t");  
  Serial.println(q);
  delay(100);
}

// -- END OF FILE --
