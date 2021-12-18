//
//    FILE: fastTrig_test2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: testing the itan functions
//    DATE: 2021-08-10
//    (c) : MIT



#include "FastTrig.h"

uint32_t start, d1, d2;

volatile float x;
int i;


void setup()
{
  Serial.begin(115200);
  Serial.println("start");

  test_tan(0);
  test_itan_error_1(false);

  Serial.println("done...\n");
}


void test_tan(int n)
{
  Serial.println(__FUNCTION__);
  Serial.print("TAN\titan\t360 calls - offset: " );
  Serial.println(n);
  delay(10);

  start = micros();
  for ( i = n; i < n + 360; i++)
  {
    x = tan(i);
  }
  float t1 = (micros() - start) / 360.0;
  Serial.println(t1);
  delay(10);

  start = micros();
  for ( i = n; i < n + 360; i++)
  {
    x = itan(i);
  }
  float t2 = (micros() - start) / 360.0;
  Serial.println(t2);
  Serial.print(t2 / t1, 3);
  Serial.println("%");
  Serial.println();
  Serial.println();
  delay(10);
}


void test_itan_error_1(bool show)
{
  Serial.println(__FUNCTION__);
  Serial.println("ITAN 0-3600 calls: \t");
  delay(10);

  float mx = 0;
  float mxr = 0;
  float z = 0;
  float zz = 0;
  for (int i = 0; i < 3600; i++)
  {
    if (((i + 900 ) % 1800) == 0) continue;
    float a = tan(i * 0.1 * PI / 180);
    float b = itan(i * 0.1);
    float y = abs(a - b);  // abs error - rel error ~ 1%
    z += y;
    if (a > 0) zz += y / a; // not 100% correct but almost.
    if (mx < y) mx = y;
    if (show)
    {
      Serial.print(i);
      Serial.print("\t");
      Serial.print(a, 6);
      Serial.print("\t");
      Serial.print(b, 6);
      Serial.print("\t");
      Serial.print(a - b, 6);
      Serial.print("\t");
      Serial.println((a - b) / a, 6);
    }
    if (abs(a) > 0.00001 && mxr < y / a)
    {
      //      Serial.print(i);
      //      Serial.print('\t');
      //      Serial.print(a, 6);
      //      Serial.print('\t');
      //      Serial.print(b, 6);
      //      Serial.print('\t');
      //      Serial.print(y/a, 6);
      //      Serial.println();
      mxr = y / a;
    }
  }
  Serial.print("max abs error: ");
  Serial.println(mx, 8);
  Serial.print("avg abs error: ");
  Serial.println(z / 3600, 8);
  Serial.print("max rel error: ");
  Serial.println(mxr, 8);
  Serial.print("avg rel error: ");
  Serial.println(zz / 3600, 8);
  Serial.println();
  Serial.println();
  delay(10);
}


void loop()
{
}


// -- END OF FILE --

