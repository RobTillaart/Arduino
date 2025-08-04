//
//    FILE: RunningMedianQuantileTest.ino
//  AUTHOR: f-s ( derived from Rob Tillaart )
// PURPOSE: demo basic quantile usage
//    DATE: 2020-09-02
//     URL: https://github.com/RobTillaart/RunningMedian


#include <RunningMedian.h>

RunningMedian samples = RunningMedian(5);


void setup()
{
  while (!Serial);  //  Wait for serial port to connect. Needed for Leonardo + MKR1010.
  Serial.begin(115200);
  delay(1000);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print(F("RUNNING_MEDIAN_VERSION: "));
  Serial.println(RUNNING_MEDIAN_VERSION);
  Serial.println();
}


void loop()
{
  test1();
}


void test1()
{
  int x = analogRead(A0);

  samples.add(x);
  //  calculate the 5% quantile => 0.05
  long q = samples.getQuantile(0.05);

  Serial.print(millis());
  Serial.print("\t");
  Serial.println(q);
  delay(100);
}


//  -- END OF FILE --

