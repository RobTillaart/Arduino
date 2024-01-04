//
//    FILE: hist_test_big.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2012-12-23
// PURPOSE: test histogram library
//     URL: https://github.com/RobTillaart/Histogram
//
//          run on ESP32 - 
//          view in Serial plotter to graph distribution


#include "histogram.h"


float b[200];   //  MIGHT NOT WORK ON AVR !!

Histogram hist(200, b);

uint32_t lastTime = 0;
const uint32_t threshold = 1000;  // milliseconds, for updating display


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HISTOGRAM_LIB_VERSION: ");
  Serial.println(HISTOGRAM_LIB_VERSION);
  Serial.println();

  //  fill the boundaries as first step
  for (int i = 0; i < 200; i++)
  {
    b[i] = i;
  }
}


void loop()
{
  //  bigger chance on 1 than on 0
  //  int x = 180 * sin(random(10000) * PI / 20000);

  //  float x = 180 * sqrt(random(1000) * 0.001);

  //  n = 1 gives flat line = uniform distribution.
  //  n = 2 gives "triangles" 
  //  n = 3 and higher some normal distribution.
  //         higher is smaller peaks.
  int x = 0;
  int n = 5;
  for (int i = 0; i < n; i++)
  {
    x += random(180);
  }
  x /= n;
  hist.add(x);


  //  update output
  uint32_t now = millis();
  if (now - lastTime > threshold)
  {
    lastTime = now;
    for (int i = 0; i < hist.size() - 1; i++)
    {
      Serial.println(hist.bucket(i));
    }
  }
}


//  -- END OF FILE --

