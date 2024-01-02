//
//    FILE: correlation_performance.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2020-05-18
// PURPOSE: demo of the Correlation Library
//     URL: https://github.com/RobTillaart/Correlation

//  performance test: only ADD and CALCULATE as these are the most used
//  and could be optimized in the future


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
  delay(100);
  C.clear();
  sum = 0;
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
  delay(100);
  start = micros();
  C.calculate();
  stop = micros();
  Serial.println(stop - start);


  Serial.println("\nCALCULATE - no new values added");
  delay(100);
  start = micros();
  C.calculate();
  stop = micros();
  Serial.println(stop - start);


  Serial.println("\ngetEstimateX");
  delay(100);
  start = micros();
  f = C.getEstimateX(42);
  stop = micros();
  Serial.println(stop - start);


  Serial.println("\ngetEstimateY");
  delay(100);
  start = micros();
  f = C.getEstimateY(42);
  stop = micros();
  Serial.println(stop - start);


  Serial.println("\ngetMaxX");
  delay(100);
  start = micros();
  f = C.getMaxX();
  stop = micros();
  Serial.println(stop - start);

  Serial.println("\ngetMinX");
  delay(100);
  start = micros();
  f = C.getMinX();
  stop = micros();
  Serial.println(stop - start);

  Serial.println("\n===================================\n\n");

  Serial.println("ADD - fill arrays again");  
  delay(100);
  C.clear();
  sum = 0;
  for (int i = 0; i < 20; i++)
  {
    f = i * 40 + 0.1 * random(10);
    start = micros();
    C.add(i * 10, f );
    stop = micros();
    sum += stop - start;
  }
  Serial.println(sum / 20.0);


  Serial.println("\ndisable R2 and E2 math from calculate");
  C.setR2Calculation(false);
  C.setE2Calculation(false);

  Serial.println("\nCALCULATE - needed ");
  delay(100);
  start = micros();
  C.calculate();
  stop = micros();
  Serial.println(stop - start);


  Serial.println("\nCALCULATE - no new values added");
  delay(100);
  start = micros();
  C.calculate();
  stop = micros();
  Serial.println(stop - start);


  Serial.println("\nCALCULATE - no new values added but forced");
  delay(100);
  start = micros();
  C.calculate(true);
  stop = micros();
  Serial.println(stop - start);


  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --

