//
//    FILE: RunningMedian_large.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo most functions
//    DATE: 2013-10-17
//     URL: https://github.com/RobTillaart/RunningMedian


#include "RunningMedian.h"


RunningMedian samples = RunningMedian(255);


long count = 0;

uint32_t start, dur1, dur2, dur3;


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

  Serial.println(samples.getSize());
}


void loop()
{
  if (count < 255)
  {
    start = micros();
    samples.add(256 - count);
    dur1 = micros() - start;
    start = micros();
    count = samples.getCount();
    dur2 = micros() - start;
    start = micros();
    float value = samples.getMedian();
    dur3 = micros() - start;

    Serial.print(count);
    Serial.print('\t');
    Serial.print(dur1);
    Serial.print('\t');
    Serial.print(dur2);
    Serial.print('\t');
    Serial.print(dur3);
    Serial.print('\t');
    Serial.print(value);
    Serial.print('\t');
    Serial.println();
  }

  if (count == 255)
  {
    for (int i = 0; i < 255; i++)
    {
      Serial.println(samples.getSortedElement(i));
    }
  }
  count++;
}


//  -- END OF FILE --

