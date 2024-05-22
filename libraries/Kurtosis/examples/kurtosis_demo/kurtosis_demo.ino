//
//    FILE: Kurtosis_demo.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2024-05-21
// PURPOSE: demo determination of skewness and kurtosis
//     URL: https://github.com/RobTillaart/Kurtosis


#include "Kurtosis.h"

Kurtosis K;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("KURTOSIS_LIB_VERSION: ");
  Serial.println(KURTOSIS_LIB_VERSION);
  Serial.println();

  K.reset();

  for (int i = 0; i < 100; i++)
  {
    int x = i;
    K.add(x);
  }
  Serial.println();
  delay(100);

  Serial.println();
  Serial.print("COUNT:\t");
  Serial.println(K.count());
  Serial.print("MEAN:\t");
  Serial.println(K.mean());
  Serial.print("VAR:\t");
  Serial.println(K.variance());
  Serial.print("STDDEV:\t");
  Serial.println(K.stddev());
  Serial.print("SKEW:\t");
  Serial.println(K.skewness());
  Serial.print("KURT:\t");
  Serial.println(K.kurtosis());
  Serial.println();

}


void loop()
{

}


//  -- END OF FILE --

