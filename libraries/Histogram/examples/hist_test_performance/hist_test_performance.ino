//
//    FILE: hist_test_performance.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2023-02-21
// PURPOSE: test histogram library
//     URL: https://github.com/RobTillaart/Histogram


#include "histogram.h"


//  boundaries does not need to be equally distributed.
float b[100];

Histogram hist(100, b);


uint32_t lastTime = 0;
const uint32_t threshold = 25;  //  in milliseconds, for updating display

uint32_t start, stop;
volatile int x;
float y;


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

  Serial.println("add 1000 random numbers");
  for (int i = 0; i < 1000; i++)
  {
    int x = random(1000);
    hist.add(x);
  }

  start = micros();
  y = hist.CDF(500);
  stop = micros();
  Serial.print("    CDF: ");
  Serial.println(y);
  Serial.print("   TIME: ");
  Serial.println(stop - start);
  delay(20);
  

  start = micros();
  y = hist.VAL(0.9);
  stop = micros();
  Serial.print("    VAL: ");
  Serial.println(y);
  Serial.print("   TIME: ");
  Serial.println(stop - start);
  delay(20);
  

  start = micros();
  x = hist.findMax();
  stop = micros();
  Serial.print("FINDMIN: ");
  Serial.println(hist.findMin());
  Serial.print("   TIME: ");
  Serial.println(stop - start);
  delay(20);
  

  start = micros();
  x = hist.findMax();
  stop = micros();
  Serial.print("FINDMIN: ");
  Serial.println(hist.findMin());
  Serial.print("   TIME: ");
  Serial.println(stop - start);
  delay(20);
  

  start = micros();
  x = hist.findMax();
  stop = micros();
  Serial.print("FINDMAX: ");
  Serial.println(hist.findMax());
  Serial.print("   TIME: ");
  Serial.println(stop - start);
  delay(20);
  

  start = micros();
  x = hist.countBelow(0);
  stop = micros();
  Serial.print("BELOW 0: ");
  Serial.println(hist.countBelow(0));
  Serial.print("   TIME: ");
  Serial.println(stop - start);
  delay(20);
  
  start = micros();
  x = hist.countLevel(0);
  stop = micros();
  Serial.print("LEVEL 0: ");
  Serial.println(hist.countLevel(0));
  Serial.print("   TIME: ");
  Serial.println(stop - start);
  delay(20);
  
  start = micros();
  x = hist.countAbove(0);
  stop = micros();
  Serial.print("ABOVE 0: ");
  Serial.println(hist.countAbove(0));
  Serial.print("   TIME: ");
  Serial.println(stop - start);
  delay(20);

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --
