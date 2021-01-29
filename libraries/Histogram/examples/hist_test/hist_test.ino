//
//    FILE: hist_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2012-12-23
//
// PUPROSE: test histogram frequency
//

#include "histogram.h"

// float b[] = { 0, 100, 200, 300, 325, 350, 375, 400, 500, 600, 700, 800, 900, 1000 };

// boundaries does not need to be equally distributed.
float b[] = { 
  0, 100, 200, 300, 325, 350, 375 };

Histogram hist(7, b);

uint32_t lastTime = 0;
const uint32_t threshold = 25;  // milliseconds, for updating display

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("\nHistogram version: ");
  Serial.println(HISTOGRAM_LIB_VERSION);

  Serial.print("# buckets: ");
  Serial.println(hist.size());

  for (int i = 0; i < hist.size()-1; i++)
  {
    Serial.print("\t");  
    Serial.print(b[i], 2);  
  }
  Serial.println();

  for (int i = 0; i < hist.size()-1; i++)
  {
    Serial.print("\t");  
    Serial.print(hist.find(b[i]));  
  }
  Serial.println();
}

void loop()
{
  // choose a "generator" for histogram data
  // int x = analogRead(A0);
  
  int x = random(600) - 50;  // below lower limit
  
  //  int x = random(25);  
  //  x = x*x;


  //  Serial.print(x);
  //  Serial.print("\t");
  //  Serial.println(hist.find(x));
  hist.add(x);

  // update output 
  uint32_t now = millis();
  if (now - lastTime > threshold)
  {
    lastTime = now;
    Serial.print(hist.count());
    for (int i = 0; i < hist.size(); i++)
    {
      Serial.print("\t");
      // gives percentage per bucket
      // Serial.print(hist.bucket(i));   
      Serial.print(hist.frequency(i), 2);  
    }
    // quartiles
    // to get at least 25% of the values you must count all values < hist.VAL(0.25);
    Serial.print("\t");
    Serial.print(hist.VAL(0.25), 2);
    // to get at least 50% of the values you must count all values < hist.VAL(0.50);
    Serial.print("\t");
    Serial.print(hist.VAL(0.50), 2);
    Serial.print("\t");
    Serial.print(hist.VAL(0.75), 2);
    Serial.print("\t");
    Serial.print(hist.VAL(1.0), 2);
    Serial.println();

    if (hist.count() > 10000UL) hist.clear();
  }
}

// END OF FILE