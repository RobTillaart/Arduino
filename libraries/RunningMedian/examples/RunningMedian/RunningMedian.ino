
#include <RunningMedian.h>

RunningMedian samples = RunningMedian(5);
RunningMedian samples2 = RunningMedian(9);

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

