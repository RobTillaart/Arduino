//
//    FILE: Fletcher32_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo

#include "Arduino.h"
#include "Fletcher32.h"
#include "printHelpers.h"  //  https://github.com/RobTillaart/printHelpers

//  expected output
//  Fletcher32_test
//  4031760169
//  4031760169
//  116654705
//  116654705
//  116982386
//  116982386
//  116720242
//  116720242


Fletcher32 fl;

char     str1[24] = "abcde";
uint16_t arr1[5]  = { 100, 120, 130, 135, 140 };
uint16_t arr2[5]  = { 101, 120, 130, 135, 140 };  // minimal diff.
uint16_t arr3[5]  = { 100, 120, 130, 135, 141 };  // minimal diff.

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.println("Fletcher32_test");

  fl.begin();
  fl.add((uint16_t *)str1, 3);
  Serial.println(fl.getFletcher());

  // Note adding per byte element is tricky
  fl.begin();
  fl.add((uint16_t)((str1[1] << 8) + str1[0]));  // note order dependency
  fl.add((uint16_t)((str1[3] << 8) + str1[2]));
  fl.add((uint16_t)(             0 + str1[4]));
  Serial.println(fl.getFletcher());

  //////////////////////////////////////////////////
  
  fl.begin();
  fl.add(arr1, 5);
  Serial.println(fl.getFletcher());

  fl.begin();
  for (int i = 0; i < 5; i++) fl.add(arr1[i]);
  Serial.println(fl.getFletcher());

  fl.begin();
  fl.add(arr2, 5);
  Serial.println(fl.getFletcher());

  fl.begin();
  for (int i = 0; i < 5; i++) fl.add(arr2[i]);
  Serial.println(fl.getFletcher());
  
  fl.begin();
  fl.add(arr3, 5);
  Serial.println(fl.getFletcher());

  fl.begin();
  for (int i = 0; i < 5; i++) fl.add(arr3[i]);
  Serial.println(fl.getFletcher());
}


void loop()
{
}


// -- END OF FILE --
