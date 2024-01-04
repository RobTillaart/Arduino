//
//    FILE: hist_find_performance.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2021-11-03
// PURPOSE: indication histogram find performance
//     URL: https://github.com/RobTillaart/Histogram


#include "histogram.h"

float b[100];

Histogram hist(100, b);

uint32_t start, duration;
uint32_t lastTime = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HISTOGRAM_LIB_VERSION: ");
  Serial.println(HISTOGRAM_LIB_VERSION);
  Serial.println();

  //  fill boundary array
  for (int i = 0; i < 100; i++) b[i] = i * 10.0;

  Serial.print("# buckets: ");
  Serial.println(hist.size());

  int x = 4;
  start = micros();
  int y = hist.find(x);
  duration = micros() - start;
  Serial.print("Duration: ");
  Serial.println(duration);
  Serial.print("  Bucket: ");
  Serial.println(y);
  delay(10);

  x = 54;
  start = micros();
  y = hist.find(x);
  duration = micros() - start;
  Serial.print("Duration: ");
  Serial.println(duration);
  Serial.print("  Bucket: ");
  Serial.println(y);
  delay(10);

  x = 654;
  start = micros();
  y = hist.find(x);
  duration = micros() - start;
  Serial.print("Duration: ");
  Serial.println(duration);
  Serial.print("  Bucket: ");
  Serial.println(y);
  delay(10);

  x = 7654;
  start = micros();
  y = hist.find(x);
  duration = micros() - start;
  Serial.print("Duration: ");
  Serial.println(duration);
  Serial.print("  Bucket: ");
  Serial.println(y);
  delay(10);

  Serial.println();
}


void loop()
{
}


//  -- END OF FILE --

