//
//    FILE: hist_test_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: make a simple plot with the histogram library
//     URL: https://github.com/RobTillaart/Histogram

//  This sketch makes a simple plot on the Serial plotter
//  Although the boundaries of the histogram are not equally distributed,
//  the columns in the plot are
//  There is a 0 value between the plots to get the (almost) vertical lines.

#include "histogram.h"


//  boundaries array does not need to be equally distributed.
float bounds[] = { 0, 100, 200, 300, 325, 350, 375, 400, 500, 600, 700, 800, 900, 1000 };

Histogram hist(14, bounds);

uint32_t lastTime = 0;
const uint32_t threshold = 5000;  //  in milliseconds, for updating display
const int SERIAL_PLOTTER_WIDTH = 500;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print(F("HISTOGRAM_LIB_VERSION: "));
  Serial.println(HISTOGRAM_LIB_VERSION);
  Serial.println();

  Serial.print("# buckets: ");
  Serial.println(hist.size());
  Serial.println();
}


void loop()
{
  //  "generator" for histogram data
  //  int x = analogRead(A0);
  int x = random(1024);
  hist.add(x);

  //  create output
  uint32_t now = millis();
  if (now - lastTime > threshold)
  {
    lastTime = now;

    //  determine column width
    int width = (SERIAL_PLOTTER_WIDTH / hist.size()) - 1;
    //  some leading zeros to remove previous columns
    for (uint16_t i = 0; i < hist.size(); i++) Serial.println(0);
    //  create the columns - equally width
    for (uint16_t i = 0; i < hist.size(); i++)
    {
      for (int w = 0; w < width; w++)
      {
        Serial.println(hist.bucket(i));
      }
      Serial.println(0);
    }
    hist.clear();
  }
}


//  -- END OF FILE --
