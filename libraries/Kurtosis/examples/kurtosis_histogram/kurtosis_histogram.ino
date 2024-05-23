//
//    FILE: kurtosis_histogram.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2024-05-21
// PURPOSE: determine skewness and kurtosis of a simple histogram
//     URL: https://github.com/RobTillaart/Kurtosis
//
//  note that the values must be added when they are produced.
//  it seems that the order of adding affects the metrics. (TODO).


#include "Kurtosis.h"

Kurtosis K1;


//  simplified histogram
uint16_t hist[100];


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("KURTOSIS_LIB_VERSION: ");
  Serial.println(KURTOSIS_LIB_VERSION);
  Serial.println();

  K1.reset();
  //  fill the histogram with 10000 measurements
  for (int i = 0; i < 10000; i++)
  {
    int x = random(100);  //  simulate measurement
    hist[x]++;
    K1.add(x);
  }

  // print statistics
  Serial.println("K1 (reference)");
  Serial.print("COUNT:\t");
  Serial.println(K1.count());
  Serial.print("MEAN:\t");
  Serial.println(K1.mean(), 4);
  Serial.print("VAR:\t");
  Serial.println(K1.variance(), 4);
  Serial.print("STDDEV:\t");
  Serial.println(K1.stddev(), 4);
  Serial.print("SKEW:\t");
  Serial.println(K1.skewness(), 4);
  Serial.print("KURT:\t");
  Serial.println(K1.kurtosis(), 4);
  Serial.println();

  for (int i = 0; i < 100; i++)
  {
    Serial.print(i);
    Serial.print("\t");
    Serial.println(hist[i]);
  }

}


void loop()
{

}


//  -- END OF FILE --
