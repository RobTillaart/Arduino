//
//    FILE: kurtosis_performance.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2024-05-21
// PURPOSE: performance measurement skewness and kurtosis
//     URL: https://github.com/RobTillaart/Kurtosis


#include "Kurtosis.h"

Kurtosis K;

volatile float x = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("KURTOSIS_LIB_VERSION: ");
  Serial.println(KURTOSIS_LIB_VERSION);
  Serial.println();
  Serial.println("times in us\n");
  delay(100);

  K.reset();

  uint32_t start = micros();
  for (int i = 0; i < 1000; i++)
  {
    K.add(i);
  }
  uint32_t stop = micros();
  Serial.print("ADD (1000x):\t");
  Serial.println((stop - start) * 0.001, 1);
  delay(100);

  start = micros();
  x = K.variance();
  stop = micros();
  Serial.print("VARIANCE 1:\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  x = K.variance();
  stop = micros();
  Serial.print("VARIANCE 2:\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  x = K.skewness();
  stop = micros();
  Serial.print("SKEWNESS:\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  x = K.kurtosis();
  stop = micros();
  Serial.print("KURTOSIS:\t");
  Serial.println(stop - start);
  delay(100);
}


void loop()
{

}


//  -- END OF FILE --
