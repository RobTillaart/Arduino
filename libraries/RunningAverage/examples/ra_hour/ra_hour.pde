#include "RunningAverage.h"

RunningAverage raMinute(60);
RunningAverage raHour(60);

int samples = 0;

void setup(void) 
{
  Serial.begin(115200);
  Serial.println("Demo RunningAverage lib - average per minute & hour");
  raHour.clr();
  raMinute.clr();
}

void loop(void) 
{
  long rn = random(0, 100);
  raMinute.add(rn);
  samples++;
  
  if (samples % 60 == 0) raHour.add(raMinute.avg());
  
  Serial.print("  raMinute: ");
  Serial.print(raMinute.avg(), 4);
  Serial.print("  raHour: ");
  Serial.println(raHour.avg(), 4);
}