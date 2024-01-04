//
//    FILE: hist_test_val.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2012-11-11
// PURPOSE: test histogram library
//     URL: https://github.com/RobTillaart/Histogram


#include "histogram.h"


float b[] = { 
  0, 50, 100, 150, 200, 250, 
  300, 350, 400, 450, 500, 
  600, 700, 800, 900, 1000 };

Histogram hist(16, b);


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
  int x = random(800);
  hist.add(x);

  Serial.print(hist.count());
  Serial.print(", ");
  float f = 0.5;
  Serial.print(f, 2);
  Serial.print(" : ");

  Serial.print(hist.VAL(f), 2);
  Serial.print("\t");

  float sum = 0;
  uint16_t i = 0;
  for (i = 0; i < hist.size(); i++)
  {
    sum += hist.frequency(i);
    Serial.print(sum, 2);
    Serial.print("\t");
    if (sum >= f) break;
  }
  Serial.print(b[i]);
  Serial.println();

  if (hist.count() > 1000)
  {
    hist.clear();
  }

  delay(10);
}


//  -- END OF FILE --

