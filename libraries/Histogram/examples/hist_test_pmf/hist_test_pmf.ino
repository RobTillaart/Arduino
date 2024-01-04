//
//    FILE: hist_test_pmf.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2012-11-10
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
  int x = random(1000);
  hist.add(x);

  Serial.print(hist.count());
  Serial.print("\t");
  for (int i = 0; i < hist.size()-1; i++)
  {
    Serial.print(hist.PMF(b[i]), 2);
    Serial.print("\t");
  }
  Serial.println();

  if (hist.count() > 1000)
  {
    hist.clear();
  }

  delay(10);
}


//  -- END OF FILE --

