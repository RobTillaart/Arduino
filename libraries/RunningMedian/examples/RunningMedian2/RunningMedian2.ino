//
//    FILE: RunningMedian2.ino
//  AUTHOR: Rob Tillaart ( kudos to Sembazuru)
// VERSION: 0.1.01
// PURPOSE: demo
//    DATE: 2013-10-17
//     URL:
//
// Released to the public domain
//

#include "RunningMedian.h"

RunningMedian samples = RunningMedian(15);

long count = 0;

void setup()
{
  Serial.begin(115200);
  Serial.print(F("Running Median Version: "));
  Serial.println(RUNNING_MEDIAN_VERSION);
}

void loop()
{
  test1();
}

void test1()
{
  if (count % 20 == 0) Serial.println(F("\nmsec \tAnR \tSize \tCnt \tLow \tAvg \tAvg(3) \tMed \tHigh"));
  count++;
  
  long x = analogRead(A0);

  samples.add(x);

  float l = samples.getLowest();
  float m = samples.getMedian();
  float a = samples.getAverage();
  float a3 = samples.getAverage(3);
  float h = samples.getHighest();
  int s = samples.getSize();
  int c = samples.getCount();

  Serial.print(millis());
  Serial.print('\t');
  Serial.print(x);
  Serial.print('\t');
  Serial.print(s);
  Serial.print('\t');
  Serial.print(c);
  Serial.print('\t');
  Serial.print(l);
  Serial.print('\t');
  Serial.print(a, 2);
  Serial.print('\t');
  Serial.print(a3, 2);
  Serial.print('\t');
  Serial.print(m);
  Serial.print('\t');
  Serial.println(h);
  delay(100);
}

