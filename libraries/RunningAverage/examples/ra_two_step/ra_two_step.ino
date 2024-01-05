//
//    FILE: ra_two_step.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo two stage statistics.
//     URL: https://github.com/RobTillaart/RunningAverage


#include "RunningAverage.h"


RunningAverage raHours(24);   //  holds hourly measurements
RunningAverage raDays(14);    //  holds min and max of the last seven days.

int samples = 0;
int day = 0;


void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RUNNINGAVERAGE_LIB_VERSION: ");
  Serial.println(RUNNINGAVERAGE_LIB_VERSION);
  raHours.clear();
  raDays.clear();
}


void loop(void)
{
  //  simulate a new hourly measurement.
  long rn = random(0, 1000);
  raHours.addValue(rn);
  samples++;

  if (samples % 24 == 0)
  {
    raDays.addValue(raHours.getMaxInBuffer());  //  track maximum of the day
    raDays.addValue(raHours.getMinInBuffer());  //  track minimum of the day
    samples = 0;
    day++;
    Serial.println();
  }

  Serial.print(day);
  Serial.print("\t");
  Serial.print(raDays.getMinInBuffer());
  Serial.print("\t");
  Serial.print(raHours.getAverage(), 2);
  Serial.print("\t");
  Serial.print(raDays.getMaxInBuffer());
  Serial.print("\t");
  Serial.println();

  delay(100);
}


//  -- END OF FILE --
