//
//    FILE: Gauss_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo


#include "Gauss.h"

Gauss G;
volatile float x;

uint32_t start;
uint32_t stop;


void setup(void)
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("GAUSS_LIB_VERSION: ");
  Serial.println(GAUSS_LIB_VERSION);
  Serial.println();
  Serial.println("Timing in micros (1000 calls)");
  Serial.println();
  
  test_1();
  test_2();
  test_3();
  test_4();
  test_5();
  test_6();

  Serial.println("\ndone...");
}


void loop(void)
{
}


void test_1()
{
  delay(10);
  G.begin(0, 1);

  start = micros();
  for (float f = -5.0; f <= 5.0; f += 0.01)
  {
    x =  G.P_smaller(f);
  }
  stop = micros();

  Serial.print("P_smaller:\t");
  Serial.print(stop - start);
  Serial.println();
}


void test_2()
{
  delay(10);
  G.begin(0, 1);

  start = micros();
  for (float f = -5.0; f <= 5.0; f += 0.01)
  {
    x =  G.P_larger(f);
  }
  stop = micros();

  Serial.print("P_larger:\t");
  Serial.print(stop - start);
  Serial.println();
}


void test_3()
{
  delay(10);
  G.begin(0, 1);

  start = micros();
  for (float f = -5.0; f <= 5.0; f += 0.01)
  {
    x =  G.P_between(0, f);
  }
  stop = micros();

  Serial.print("P_between:\t");
  Serial.print(stop - start);
  Serial.println();
}


void test_4()
{
  delay(10);
  G.begin(0, 1);

  start = micros();
  for (float f = -5.0; f <= 5.0; f += 0.01)
  {
    x =  G.normalize(f);
  }
  stop = micros();

  Serial.print("normalize:\t");
  Serial.print(stop - start);
  Serial.println();
}


void test_5()
{
  delay(10);
  G.begin(0, 1);

  start = micros();
  for (float f = -5.0; f <= 5.0; f += 0.01)
  {
    x = G.bellCurve(f);
  }
  stop = micros();

  Serial.print("bellCurve:\t");
  Serial.print(stop - start);
  Serial.println();
}


void test_6()
{
  delay(10);
  G.begin(0, 1);

  float cf = 0.52330751;  //  See Gauss_test_bell_curve.ino
  start = micros();
  for (float f = -5.0; f <= 5.0; f += 0.01)
  {
    float a = G.P_smaller(f - cf);
    float b = G.P_smaller(f + cf);
    x = a - b;
  }
  stop = micros();

  Serial.print("approx.bell:\t");
  Serial.print(stop - start);
  Serial.println();
}


// -- END OF FILE --
