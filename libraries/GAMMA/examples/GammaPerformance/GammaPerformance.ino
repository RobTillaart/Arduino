//
//    FILE: gammaPerformance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo


#include "gamma.h"


GAMMA gt1(256);
GAMMA gt2(128);
GAMMA gt3(64);
GAMMA gt4(32);
GAMMA gt5(16);

uint32_t start, d1;
volatile int x;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("GAMMA_LIB_VERSION: ");
  Serial.println(GAMMA_LIB_VERSION);

  gt1.begin();
  gt2.begin();
  gt3.begin();
  gt4.begin();
  gt5.begin();

  Serial.println("\ntiming in microseconds\n");

  Serial.println("SETGAMMA");
  Serial.println("SIZE\tTIME\tTIME per element");
  test_setGamma(gt1);
  test_setGamma(gt2);
  test_setGamma(gt3);
  test_setGamma(gt4);
  test_setGamma(gt5);
  Serial.println();

  Serial.println("SETGAMMA II");
  Serial.println("SIZE\tTIME\tTIME per element");
  test_setGamma(gt1);
  test_setGamma(gt2);
  test_setGamma(gt3);
  test_setGamma(gt4);
  test_setGamma(gt5);
  Serial.println();

  Serial.println("GET[]");
  Serial.println("SIZE\tTIME\tTIME per element");
  test_index(gt1);
  test_index(gt2);
  test_index(gt3);
  test_index(gt4);
  test_index(gt5);
  Serial.println();

  Serial.println("\ndone...");
}


void test_setGamma(GAMMA & gt)
{
  start = micros();
  gt.setGamma(2.2);
  d1 = micros() - start;
  Serial.print(gt.size());
  Serial.print('\t');
  Serial.print(d1);
  Serial.print('\t');
  Serial.println(1.0 * d1 / gt.size());
  delay(10);
}


void test_index(GAMMA & gt)
{
  start = micros();
  for (int i = 0; i < 256; i++)
  {
    x = gt[i];
  }
  d1 = micros() - start;
  Serial.print(gt.size());
  Serial.print('\t');
  Serial.print(d1);
  Serial.print('\t');
  Serial.println(d1 / 256.0);
  delay(10);
}


void loop()
{
}


// -- END OF FILE --

