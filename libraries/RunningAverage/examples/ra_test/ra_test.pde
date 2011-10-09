#include "RunningAverage.h"

RunningAverage myRA(10); // use default size
int samples = 0;

void setup(void) 
{
  Serial.begin(115200);
  Serial.println("Demo RunningAverage lib");
  myRA.clr(); // explicitly start clean
}

void loop(void) 
{
  long rn = random(0, 100);
  myRA.add(rn/100.0);
  samples++;
  Serial.print("Running Average: ");
  Serial.println(myRA.avg(), 4);
  
  if (samples == 300)
  {
    samples = 0;
    myRA.clr();
  }
  delay(100);
}