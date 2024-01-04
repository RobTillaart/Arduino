//
//    FILE: hist_test_level.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2021-11-04
// PURPOSE: test histogram library
//     URL: https://github.com/RobTillaart/Histogram


#include "histogram.h"


//  boundaries does not need to be equally distributed.
float b[100];

Histogram hist(100, b);

uint32_t lastTime = 0;
const uint32_t threshold = 25;  //  in milliseconds, for updating display


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HISTOGRAM_LIB_VERSION: ");
  Serial.println(HISTOGRAM_LIB_VERSION);
  Serial.println();

  // fill boundary array
  for (int i = 0; i < 100; i++)
  {
    b[i] = i * 10.0;
  }
  Serial.print("# buckets: ");
  Serial.println(hist.size());

  Serial.print("BELOW 0: ");
  Serial.println(hist.countBelow(0));
  Serial.print("LEVEL 0: ");
  Serial.println(hist.countLevel(0));
  Serial.print("ABOVE 0: ");
  Serial.println(hist.countAbove(0));
  Serial.print("COUNT  : ");
  Serial.println(hist.count());
  Serial.println();

  Serial.println("add 100 random numbers");
  for (int i = 0; i < 100; i++)
  {
    int x = random(1000);
    hist.add(x);
  }

  Serial.print("BELOW 0: ");
  Serial.println(hist.countBelow(0));
  Serial.print("LEVEL 0: ");
  Serial.println(hist.countLevel(0));
  Serial.print("ABOVE 0: ");
  Serial.println(hist.countAbove(0));
  Serial.print("COUNT  : ");
  Serial.println(hist.count());
  Serial.println();

  Serial.println("sub 100 random numbers");
  for (int i = 0; i < 100; i++)
  {
    int x = random(1000);
    hist.sub(x);
  }

  Serial.print("BELOW 0: ");
  Serial.println(hist.countBelow(0));
  Serial.print("LEVEL 0: ");
  Serial.println(hist.countLevel(0));
  Serial.print("ABOVE 0: ");
  Serial.println(hist.countAbove(0));
  Serial.print("COUNT  : ");
  Serial.println(hist.count());
  Serial.println();

  int minidx = hist.findMin();
  int maxidx = hist.findMax();
  Serial.print("MIN INDEX: ");
  Serial.print(minidx);
  Serial.print("\t");
  Serial.println(hist.bucket(minidx));
  Serial.print("MAX INDEX: ");
  Serial.print(maxidx);
  Serial.print("\t");
  Serial.println(hist.bucket(maxidx));
  Serial.println();

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --

