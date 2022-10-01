//
//    FILE: fastTrig_test1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: testing the fastTrigonio functions
//    DATE: 2020-08-30
//    (c) : MIT
//


#include "FastTrig.h"

uint32_t start, d1, d2;

volatile float x;
int i;


void setup()
{
  Serial.begin(115200);
  Serial.println("start");

  test_hw_support();

  test_sin_cos_tan(0);
  test_isin_icos_itan(0);
  test_sin_cos_tan(720);
  test_isin_icos_itan(720);

  test_isin_error_1(false);  // parameter true gives a more info
  test_icos_error_1(false);
  test_itan_error_1(false);

  Serial.println("done...\n");
}


bool test_hw_support()        // to be elaborated
{
  Serial.println(__FUNCTION__);
  int n = random(350);
  start = micros();
  volatile float x = sin(n);
  d1 = micros() - start;
  start = micros();
  volatile float y = x / 3.14;
  d2 = micros() - start;
  Serial.println(d1);
  Serial.println(d2);
  Serial.println(y);      //  keep compiler happy
  Serial.println();
  return (d1 / d2) < 1.5; //  just a guess for now.
}


void test_sin_cos_tan(int n)
{
  Serial.println(__FUNCTION__);
  Serial.print("SIN\tCOS\tTAN\t360 calls - offset: " );
  Serial.println(n);
  delay(10);
  start = micros();
  for ( i = n; i < n + 360; i++)
  {
    x = sin(i);
  }
  Serial.print((micros() - start) / 360.0);
  Serial.print('\t');
  delay(10);

  start = micros();
  for ( i = n; i < n + 360; i++)
  {
    x = cos(i);
  }
  Serial.print((micros() - start) / 360.0);
  Serial.print('\t');
  delay(10);

  start = micros();
  for ( i = n; i < n + 360; i++)
  {
    x = tan(i);
  }
  Serial.println((micros() - start) / 360.0);
  Serial.println();
  Serial.println();
  delay(10);
}


void test_isin_icos_itan(int n)
{
  Serial.println(__FUNCTION__);
  Serial.print("ISIN\tICOS\tITAN\t360 calls - offset: " );
  Serial.println(n);
  delay(10);
  start = micros();
  for ( i = n; i < n + 360; i++)
  {
    x = isin(i);
  }
  Serial.print((micros() - start) / 360.0);
  Serial.print('\t');
  delay(10);

  start = micros();
  for ( i = n; i < n + 360; i++)
  {
    x = icos(i);
  }
  Serial.print((micros() - start) / 360.0);
  Serial.print('\t');
  delay(10);

  start = micros();
  for ( i = n; i < n + 360; i++)
  {
    x = itan(i);
  }
  Serial.println((micros() - start) / 360.0);
  Serial.println();
  Serial.println();
  delay(10);
}


void test_isin_error_1(bool show)
{
  Serial.println(__FUNCTION__);
  Serial.println("ISIN 0-3600 calls: \t");
  delay(10);

  float mx = 0;
  float mxr = 0;
  float z = 0;
  float zz = 0;
  for ( i = 0; i <= 3600; i++)
  {
    float a = sin(i * 0.1 * PI / 180);
    float b = isin(i * 0.1);
    float y = abs(a - b);
    z += y;
    if (a > 0) zz += y / a; // not 100% correct but almost.
    if (mx < y)
    {
      mx = y;
      if (show)
      {
        Serial.print(i);
        Serial.print("\t");
        Serial.print(a, 6);
        Serial.print("\t");
        Serial.print(b, 6);
        Serial.print("\t");
        Serial.println(a - b, 6);
      }
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


void test_icos_error_1(bool show)
{
  Serial.println(__FUNCTION__);
  Serial.println("ICOS 0-3600 calls:\t");
  delay(10);

  float mx = 0;
  float mxr = 0;
  float z = 0;
  float zz = 0;
  for ( i = 0; i < 3600; i++)
  {
    float a = cos(i * 0.1 * PI / 180);
    float b = icos(i * 0.1);
    float y = abs(a - b);
    z += y;
    if (a > 0) zz += y / a; // not 100% correct but almost.
    if (mx < y)
    {
      mx = y;
      if (show)
      {
        Serial.print(i);
        Serial.print("\t");
        Serial.print(a, 6);
        Serial.print("\t");
        Serial.print(b, 6);
        Serial.print("\t");
        Serial.println(a - b, 6);
      }
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


void test_itan_error_1(bool show)
{
  Serial.println(__FUNCTION__);
  Serial.println("ITAN 0-3600 calls: \t");
  delay(10);

  float mx = 0;
  float mxr = 0;
  float z = 0;
  float zz = 0;
  for ( i = -0; i < 3600; i++)
  {
    if ((i + 900 ) % 1800 == 0) continue;
    float a = tan(i * 0.1 * PI / 180);
    float b = itan(i * 0.1);
    float y = abs(a - b);  // abs error - rel error ~ 1%
    z += y;
    if (a > 0) zz += y / a; // not 100% correct but almost.
    if (mx < y)
    {
      mx = y;
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
