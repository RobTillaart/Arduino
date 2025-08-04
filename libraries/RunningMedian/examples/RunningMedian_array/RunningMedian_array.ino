//
//    FILE: RunningMedian.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: array of runningMedian objects
//    DATE: 2022-06-21
//     URL: https://github.com/RobTillaart/RunningMedian


#include <RunningMedian.h>

RunningMedian a(5);
RunningMedian b(10);
RunningMedian c(15);
RunningMedian d(20);

RunningMedian RM[4] = { a, b, c, d };


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
  for (int i = 0; i < 4; i++)
  {
    RM[i].add(random(100));
  }
  for (int i = 0; i < 4; i++)
  {
    Serial.print(RM[i].getCount());
    Serial.print("\t");
    Serial.print(RM[i].getMedian());
    Serial.print("\t");
  }
  Serial.println();
  delay(100);
}


//  -- END OF FILE --
