//
//    FILE: correlation_test.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2020-05-18
// PURPOSE: demo of the Correlation Library
//     URL: https://github.com/RobTillaart/Correlation

//  performance test: 
//  only ADD and CALCULATE as these are the most used
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
  delay(10);
  C.clear();
  for (int i = 0; i < 20; i++)
  {
    f = i * -40 + 0.2 * random(10);
    start = micros();
    C.add(i * 10, f );
    Serial.print(i * 10);
    Serial.print(" ");
    Serial.println(f);
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
  Serial.println();

  Serial.println(C.getSumXY(), 6);
  Serial.println(C.getSumX2(), 6);
  Serial.println(C.getSumY2(), 6);
  Serial.println(C.getRsquare(), 6);
  Serial.println(C.getR(), 6);
  Serial.print("A: ");
  Serial.println(C.getA());
  Serial.print("B: ");
  Serial.println(C.getB());
  Serial.println();


  start = micros();
  float COV = C.getSumXY() / ((C.count() - 1));
  float R = C.getSumXY() / sqrt(C.getSumX2() * C.getSumY2());
  stop = micros();
  Serial.println(stop - start);
  Serial.print("COV: ");
  Serial.println(COV);
  Serial.print("R: ");
  Serial.println(R, 6);

  //  test();
  Serial.println("\nDone...");
}


void loop()
{
}


void test()
{
  C.clear();

  C.add(2, 7);
  C.add(3, 9);
  C.add(4, 10);
  C.add(5, 14);
  C.add(6, 15);

  C.calculate();

  Serial.println("---------------");
  Serial.println(C.getSumXY(), 6);
  Serial.println(C.getSumX2(), 6);
  Serial.println(C.getSumY2(), 6);
  Serial.println(C.getRsquare(), 6);
  Serial.println(C.getR(), 6);
  Serial.print("A: ");
  Serial.println(C.getA());
  Serial.print("B: ");
  Serial.println(C.getB());
  Serial.println();

  //  assertEqualFloat(2.6, C.getA(), 0.0001);
  //  assertEqualFloat(2.1, C.getB(), 0.0001);
  //  assertEqualFloat(0.97913, C.getR(), 0.0001);
  //  assertEqualFloat(0.958696, C.getRsquare(), 0.0001);
  //  assertEqualFloat(1.9, C.getEsquare(), 0.0001);
}


//  -- END OF FILE --

