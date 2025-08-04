//
//    FILE: RunningMedian_getMedianAverage.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test sketch to show the difference between
//          getAverage(nMedian) and getMedianAverage(nMedian).
//     URL: https://github.com/RobTillaart/RunningMedian


#include <RunningMedian.h>

RunningMedian samples = RunningMedian(11);


void test_compare()
{
  Serial.println(__FUNCTION__);
  for (int x = 0; x < 9; x++)
  {
    for (int y = 0; y <= x; y++)
    {
      float a = samples.getAverage(y);
      float b = samples.getMedianAverage(y);
      Serial.print(x);
      Serial.print('\t');
      Serial.print(y);
      Serial.print('\t');
      Serial.print(a, 4);
      Serial.print('\t');
      Serial.print(b, 4);
      Serial.print('\t');
      Serial.println(a - b, 4);
    }
    Serial.println();

    samples.add(x);
  }
}


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

  test_compare();

  samples.clear();
  samples.add(1);
  samples.add(2);

  delay(1000);
  uint32_t start = micros();
  float f = samples.getMedianAverage(1);
  uint32_t stop = micros();
  Serial.println(stop - start);
  Serial.println(f);
}


void loop()
{
}


//  -- END OF FILE --
