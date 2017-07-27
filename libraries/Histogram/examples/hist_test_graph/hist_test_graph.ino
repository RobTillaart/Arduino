//
//    FILE: hist_test_graph.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2017-07-16
//
// PUPROSE: test histogram frequency
//

#include "histogram.h"

// boundaries array does not need to be equally distributed.
float bounds[] = { 0, 100, 200, 300, 325, 350, 375, 400, 500, 600, 700, 800, 900, 1000 };

Histogram hist(14, bounds);

uint32_t lastTime = 0;
const uint32_t threshold = 1000;  // milliseconds, for updating display

void setup()
{
  Serial.begin(115200);
  Serial.print(__FILE__);
  Serial.print("\nHistogram version: ");
  Serial.println(HISTOGRAM_LIB_VERSION);

  Serial.print("# buckets: ");
  Serial.println(hist.size());
  Serial.println();
}

void loop()
{
  // "generator" for histogram data
  int x = analogRead(A0);
  hist.add(x);

  // update output 
  uint32_t now = millis();
  if (now - lastTime > threshold)
  {
    lastTime = now;

    for (int i = 0; i < hist.size(); i++)
    {
      Serial.print(i);
      Serial.print("\t");
      Serial.print(hist.frequency(i), 2);
      Serial.print("\t");

      int n = hist.frequency(i) * 50;  // 0..50
      Serial.print(n);
      Serial.print("\t");
      for (int p = 0; p < n; p++)
      {
        Serial.print(']');
      }
      Serial.println();
    }
    if (hist.count() > 1000000UL) hist.clear();
  }
}

