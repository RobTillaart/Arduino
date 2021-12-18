//
//    FILE: fastTrig_test_arc.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: testing the fastTrigonio functions
//    DATE: 2020-09-09



#include "FastTrig.h"

uint32_t start, d1, d2;

volatile float x;
int i;
float f;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  test_arcsin_arccos_arctan();
  test_i_arcsin_i_arccos_i_arctan();

  test_i_arcsin_error_1(true);  // parameter true gives a more info
  test_i_arccos_error_1(true);

  // NOT IMPLEMENTED
  //test_i_arctan_error_1(true);

  Serial.println("done...\n");
}


/////////////////////////////////////////////////////////////
//
//
//
void test_arcsin_arccos_arctan()
{
  Serial.println(__FUNCTION__);
  Serial.println("ASIN\tACOS\tATAN\t2000 calls " );
  Serial.flush();
  start = micros();
  for ( f = -1.0; f <= 1.0; f += 0.001)
  {
    x = asin(f);
  }
  Serial.print((micros() - start) / 2000.0);
  Serial.print('\t');
  Serial.flush();

  start = micros();
  for ( f = -1.0; f <= 1.0; f += 0.001)
  {
    x = acos(f);
  }
  Serial.print((micros() - start) / 2000.0);
  Serial.print('\t');
  Serial.flush();

  start = micros();
  for ( f = -1.0; f <= 1.0; f += 0.001)
  {
    x = atan(f);
  }
  Serial.println((micros() - start) / 2000.0);
  Serial.println();
  Serial.println();
  Serial.flush();
}


void test_i_arcsin_i_arccos_i_arctan()
{
  Serial.println(__FUNCTION__);
  Serial.println("IASIN\tIACOS\tIATAN\t2000 calls" );
  Serial.flush();
  start = micros();
  for ( f = -1.0; f <= 1.0; f += 0.001)
  {
    x = iasin(f);
  }
  Serial.print((micros() - start) / 2000.0);
  Serial.print('\t');
  Serial.flush();

  start = micros();
  for ( f = -1.0; f <= 1.0; f += 0.001)
  {
    x = iacos(f);
  }
  Serial.print((micros() - start) / 2000.0);
  Serial.print('\t');
  Serial.flush();

  start = micros();
  for ( f = -1.0; f <= 1.0; f += 0.001)
  {
    x = iatan(f);
  }
  Serial.println((micros() - start) / 2000.0);
  Serial.println();
  Serial.println();
  Serial.flush();
}


void test_i_arcsin_error_1(bool show)
{
  Serial.println(__FUNCTION__);
  Serial.println("I_ARCSIN 2000 calls: \t");
  Serial.flush();

  float mx = 0;
  float mxr = 0;
  float z = 0;
  float zz = 0;
  for ( f = -1.0; f <= 1.0; f += 0.001)
  {
    float a = asin(f) * 180 / PI;
    float b = iasin(f);
    float y = abs(a - b);
    z += y;
    if (a > 0) zz += y / a; // not 100% correct but almost.
    if (mx < y)
    {
      mx = y;
      if (show)
      {
        Serial.print(f, 6);
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
  Serial.flush();
}


void test_i_arccos_error_1(bool show)
{
  Serial.println(__FUNCTION__);
  Serial.println("I_ARCCOS 2000 calls:\t");
  Serial.flush();

  float mx = 0;
  float mxr = 0;
  float z = 0;
  float zz = 0;
  for ( f = -1.0; f <= 1.0; f += 0.001)
  {
    float a = acos(f) * 180 / PI;
    float b = iacos(f);
    float y = abs(a - b);
    z += y;
    if (a > 0) zz += y / a; // not 100% correct but almost.
    if (mx < y)
    {
      mx = y;
      if (show)
      {
        Serial.print(f, 6);
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
  Serial.flush();
}


void test_i_arctan_error_1(bool show)
{
  Serial.println(__FUNCTION__);
  Serial.println("I_ARCTAN 2000 calls: \t");
  Serial.flush();

  float mx = 0;
  float mxr = 0;
  float z = 0;
  float zz = 0;
  for ( f = -1000.0; f <= 1000.0; f++)
  {
    if (f == 0) continue;
    float a = atan(f) * 180 / PI;
    float b = iatan(f);
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
  Serial.flush();
}


void loop()
{
}


// -- END OF FILE --

