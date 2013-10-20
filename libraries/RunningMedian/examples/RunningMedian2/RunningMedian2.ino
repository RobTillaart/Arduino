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

RunningMedian samples = RunningMedian(100);

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
  if (count % 20 == 0) Serial.println(F("\nmsec \tAnR \tSize \tCnt \tLow \tAvg \tAvg(7) \tAvg(3) \tMed \tHigh \tPre(1) \tPre(2)"));
  count++;

  long x = analogRead(A0);

  samples.add(x);

  float l = samples.getLowest();
  float m = samples.getMedian();
  float a = samples.getAverage();
  float a7 = samples.getAverage(7);
  float a3 = samples.getAverage(3);
  float h = samples.getHighest();
  int s = samples.getSize();
  int c = samples.getCount();
  float p1 = samples.predict(1);
  float p2 = samples.predict(2);

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
  Serial.print(a7, 2);
  Serial.print('\t');
  Serial.print(a3, 2);
  Serial.print('\t');
  Serial.print(m);
  Serial.print('\t');
  Serial.print(h);
  Serial.print('\t');
  Serial.print(p1, 2);
  Serial.print('\t');
  Serial.println(p2, 2);

  delay(100);
}


