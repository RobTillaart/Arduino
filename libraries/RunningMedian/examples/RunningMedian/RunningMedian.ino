//
//    FILE: RunningMedian.ino
//  AUTHOR: Rob Tillaart ( kudos to Sembazuru)
// PURPOSE: demo basic usage
//    DATE: 2013-10-17
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
  long l = samples.getLowest();
  long m = samples.getMedian();
  long a = samples.getAverage();
  long h = samples.getHighest();

  Serial.print(millis());
  Serial.print("\t");
  Serial.print(x);
  Serial.print("\t");
  Serial.print(l);
  Serial.print("\t");
  Serial.print(a);
  Serial.print("\t");
  Serial.print(m);
  Serial.print("\t");
  Serial.println(h);
  delay(100);
}


//  -- END OF FILE --

