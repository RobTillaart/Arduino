//
//    FILE: Fletcher64_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo

#include "Arduino.h"
#include "Fletcher64.h"
#include "printHelpers.h"  //  https://github.com/RobTillaart/printHelpers

//  expected output
//  Fletcher64_test
//  14467467625952928454
//  14467467625952928454
//  7645041787505
//  7645041787505
//  7666516623986
//  7666516623986
//  7649336754802
//  7649336754802


Fletcher64 fl;

char     str1[24] = "abcde";
uint32_t arr1[5]  = { 100, 120, 130, 135, 140 };
uint32_t arr2[5]  = { 101, 120, 130, 135, 140 };  // minimal diff.
uint32_t arr3[5]  = { 100, 120, 130, 135, 141 };  // minimal diff.

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.println("Fletcher64_test");

  fl.begin();
  fl.add((uint32_t *)str1, 2);
  Serial.println(print64(fl.getFletcher()));

  // Note adding per byte element is tricky => order dependency
  fl.begin();
  uint32_t t = str1[3];
  t <<= 8;
  t += str1[2];
  t <<= 8;
  t += str1[1];
  t <<= 8;
  t += str1[0];

  fl.add(t);
  fl.add(str1[4]);
  Serial.println(print64(fl.getFletcher()));

  //////////////////////////////////////////////////

  fl.begin();
  fl.add(arr1, 5);
  Serial.println(print64(fl.getFletcher()));

  fl.begin();
  for (int i = 0; i < 5; i++) fl.add(arr1[i]);
  Serial.println(print64(fl.getFletcher()));

  fl.begin();
  fl.add(arr2, 5);
  Serial.println(print64(fl.getFletcher()));

  fl.begin();
  for (int i = 0; i < 5; i++) fl.add(arr2[i]);
  Serial.println(print64(fl.getFletcher()));

  fl.begin();
  fl.add(arr3, 5);
  Serial.println(print64(fl.getFletcher()));

  fl.begin();
  for (int i = 0; i < 5; i++) fl.add(arr3[i]);
  Serial.println(print64(fl.getFletcher()));
}


void loop()
{
}


// -- END OF FILE --
