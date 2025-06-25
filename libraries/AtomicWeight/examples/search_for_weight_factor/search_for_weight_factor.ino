//    FILE: search_for_weight_factor.ino
//  AUTHOR: Rob Tillaart
//     URL: https://github.com/RobTillaart/AtomicWeight
// PURPOSE: find an optimal weight factor.
//
//
//  takes serious time
//
//  best relative error found so far
//  FACTOR    SUM     REL           MAXVAL
//  201.3868  0.1383  8.865   8.865  59208  (that is  0.008%)


#include "Arduino.h"
#include "elements_float.h"


float best  = 202;
float error = 10000;


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println();

  float minError = 100;
  for (float factor = 197.0; factor <= 223.0; factor += 0.001)
  {
    float sum = 0;
    float mx  = 0;
    uint32_t val;
    for (int i = 0; i < 119; i++)
    {
      val = round(elements[i].weight * factor);
      float absError = abs( elements[i].weight - val / factor);
      float relError =  absError / elements[i].weight;
      if (relError > mx) mx = relError;
      sum += absError;
    }
    if (mx < minError)
    {
      minError = mx;
      Serial.print(factor, 4);
      Serial.print("\t");
      Serial.print(sum, 4);
      Serial.print("\t");
      Serial.print(mx * 100, 3);
      Serial.print("\t");
      Serial.print(minError * 100, 3);
      Serial.print("\t");
      Serial.println(val);
    }
  }
  Serial.println("\ndone");
}


void loop()
{
}


//  -- END OF FILE --

