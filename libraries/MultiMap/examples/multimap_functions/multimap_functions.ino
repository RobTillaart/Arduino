//
//    FILE: multimap_functions.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo (use serial plotter)...
//    DATE: 2020-04-09
//    (c) : MIT
//
//  example show use of multiMap to approximate some well known functions.


#include "MultiMap.h"


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MULTIMAP_LIB_VERSION: ");
  Serial.println(MULTIMAP_LIB_VERSION);
  Serial.println();
  delay(100);

  test_normal_distribution();
  test_sinus();
  lest_log10();
  test_exp2();
  test_exp3();
  test_sawtooth();

  Serial.println("\nDone...");
}


void loop()
{
}


void test_normal_distribution()
{
  //  sort of normal distribution
  long norm_dist[] = { 0, 5, 20, 50, 80, 95, 100, 95, 80, 50, 20, 5, 0 };  // 13
  long in[13];
  for (int i = 0; i < 13; i++) in[i] = round(i * 1000.0 / 12);
  for (int i = 0; i <= 1000; i += 10)
  {
    long y = multiMap<long>(i, in, norm_dist, 13);
    //    Serial.print(i);
    //    Serial.print(" => ");
    Serial.println(y);
    delay(10);
  }
}


void test_sinus()
{
  //  one sinus wave, amplitude 1023
  long sinus[] = {0, 316, 601, 827, 972, 1023, 972, 827, 601, 316, 0, -316, -601, -827, -972, -1023, -972, -827, -601, -316, 0 }; //21
  long in[21];
  for (int i = 0; i < 21; i++) in[i] = round(i * 1000.0 / 20);
  for (int i = 0; i <= 1000; i += 10)
  {
    long y = multiMap<long>(i, in, sinus, 21);
    //    Serial.print(i);
    //    Serial.print(" => ");
    Serial.println(y);
    delay(10);
  }
}


void lest_log10()
{
  //  log10 * 100
  long _log10[] = { -1000000, 460, 529, 570, 599, 621, 639, 655, 668, 680, 690}; // size 11
  long in[11];
  for (int i = 0; i < 11; i++) in[i] = round(i * 1000.0 / 10);
  for (int i = 100; i <= 1000; i += 10)
  {
    long y = multiMap<long>(i, in, _log10, 11);
    //    Serial.print(i);
    //    Serial.print(" => ");
    Serial.println(y);
    delay(10);
  }
}


void test_exp2()
{
  //  2^x
  long _exp2[] = { 0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };  // size 12
  long in[12];
  for (int i = 0; i < 12; i++) in[i] = round(i * 1000.0 / 11);
  for (int i = 0; i <= 1000; i += 10)
  {
    long y = multiMap<long>(i, in, _exp2, 12);
    //    Serial.print(i);
    //    Serial.print(" => ");
    Serial.println(y);
    delay(10);
  }
}


void test_exp3()
{
  //  3^x
  long _exp3[] = { 0, 1, 3, 9, 27, 81, 243, 729, 2187, 6561 }; // size 10
  long in[10];
  for (int i = 0; i < 10; i++) in[i] = round(i * 1000.0 / 9);
  for (int i = 0; i <= 1000; i += 10)
  {
    long y = multiMap<long>(i, in, _exp3, 10);
    //    Serial.print(i);
    //    Serial.print(" => ");
    Serial.println(y);
    delay(10);
  }
}


void test_sawtooth()
{
  long sawtooth[] = { 0, 1000, 0, -1000, 0, 1000, -1000, 0 }; // size 8
  long in[8];
  for (int i = 0; i < 8; i++) in[i] = round(i * 1000.0 / 7);
  for (int i = 0; i <= 1000; i += 10)
  {
    long y = multiMap<long>(i, in, sawtooth, 8);
    //    Serial.print(i);
    //    Serial.print(" => ");
    Serial.println(y);
    delay(10);
  }
}


//  -- END OF FILE --

