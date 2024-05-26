//
//    FILE: hist_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo histogram array
//     URL: https://github.com/RobTillaart/Histogram


#include "histogram.h"


//  float b[] = { 0, 100, 200, 300, 325, 350, 375, 400, 500, 600, 700, 800, 900, 1000 };

//  boundaries does not need to be equally distributed.
float a[] = {
  0, 50, 125, 200, 250, 350, 500
};
float b[] = {
  0, 100, 200, 300, 325, 350, 375, 450
};

Histogram hist[2] = { Histogram(7, a), Histogram(8, b)};

uint32_t lastTime = 0;
const uint32_t threshold = 25;  //  in milliseconds, for updating display


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HISTOGRAM_LIB_VERSION: ");
  Serial.println(HISTOGRAM_LIB_VERSION);
  Serial.println();

}


void loop()
{
  //  choose a "generator" for histogram data
  //  int x = analogRead(A0);

  int x = random(600) - 50;  // below lower limit

  hist[0].add(x);
  hist[1].add(x);

  // update output
  uint32_t now = millis();
  if (now - lastTime > threshold)
  {
    lastTime = now;
    Serial.print(hist[0].count());
    for (uint16_t i = 0; i < hist[0].size(); i++)
    {
      Serial.print("\t");
      Serial.print(hist[0].frequency(i), 2);
    }
    Serial.println();

    Serial.print(hist[1].count());
    for (uint16_t i = 0; i < hist[1].size(); i++)
    {
      Serial.print("\t");
      Serial.print(hist[1].frequency(i), 2);
    }
    Serial.println();

    if (hist[0].count() > 10000UL) hist[0].clear();
    if (hist[1].count() > 10000UL) hist[1].clear();
  }
}


//  -- END OF FILE --
