//
//    FILE: runningAngle_0_360.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo mapping average from -180..180 to 0..360


#include "runningAngle.h"

uint32_t start, stop;


runningAngle heading(runningAngle::DEGREES);

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  start = millis();
  for (int32_t a = 0; a < 36000; a++)
  {
    heading.reset();
    float angle = a * 0.01;
    heading.add(angle);

    float average = heading.getAverage();
    //  map output 0..359.999
    if (average < 0)
    {
      average += 360.0;
    }

    if (abs(angle - average) > 0.0001)
    {
      Serial.print(angle);
      Serial.print("\t");
      Serial.print(average);
      Serial.println();
    }
  }
  stop = millis();
  Serial.println();
  Serial.print("TIME: \t");
  Serial.println(stop - start);
  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --
