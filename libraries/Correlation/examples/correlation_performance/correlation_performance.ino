//
//    FILE: correlation_performance.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2020-05-18
// VERSION: 0.1.1
// PUPROSE: demo of the Correlation Library

// performance test: only ADD and CALCULATE as these are the most used
// and could be optimized in the future


#include "Correlation.h"

Correlation C(100);

uint32_t start, stop, sum = 0;

volatile float f;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("CORRELATION_LIB_VERSION: ");
  Serial.println(CORRELATION_LIB_VERSION);

  Serial.println("ADD");
  delay(10);
  C.clear();
  for (int i = 0; i < 20; i++)
  {
    f = i * 40 + 0.1 * random(10);
    start = micros();
    C.add(i * 10, f );
    stop = micros();
    sum += stop - start;
  }
  Serial.println(sum / 20.0);


  Serial.println("\nCALCULATE - needed ");
  delay(10);
  start = micros();
  C.calculate();
  stop = micros();
  Serial.println(stop - start);

  Serial.println("\nCALCULATE - no new values added");
  delay(10);
  start = micros();
  C.calculate();
  stop = micros();
  Serial.println(stop - start);


  Serial.println("\ngetEstimateX");
  delay(10);
  start = micros();
  f = C.getEstimateX(42);
  stop = micros();
  Serial.println(stop - start);


  Serial.println("\ngetEstimateY");
  delay(10);
  start = micros();
  f = C.getEstimateY(42);
  stop = micros();
  Serial.println(stop - start);


  Serial.println("\ngetMaxX");
  delay(10);
  start = micros();
  f = C.getMaxX();
  stop = micros();
  Serial.println(stop - start);

  Serial.println("\nDone...");
}

void loop()
{

}

// -- END OF FILE --
