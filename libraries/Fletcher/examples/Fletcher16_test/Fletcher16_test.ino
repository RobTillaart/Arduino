//
//    FILE: Fletcher16_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo

#include "Arduino.h"
#include "Fletcher16.h"
#include "printHelpers.h"  //  https://github.com/RobTillaart/printHelpers

//  expected output
//  Fletcher16_test
//  51440
//  51440
//  8279
//  8279
//  1575
//  1575

Fletcher16 fl;

char str1[24] = "abcde";
char str2[24] = "abcdef";
char str3[24] = "abcdefgh";


void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.println("Fletcher16_test");

  fl.begin();
  fl.add((uint8_t *)str1, 5);
  Serial.println(fl.getFletcher());

  fl.begin();
  for (int i = 0; i < 5; i++) fl.add((uint8_t)str1[i]);
  Serial.println(fl.getFletcher());

  fl.begin();
  fl.add((uint8_t *)str2, 6);
  Serial.println(fl.getFletcher());

  fl.begin();
  for (int i = 0; i < 6; i++) fl.add((uint8_t)str2[i]);
  Serial.println(fl.getFletcher());

  fl.begin();
  fl.add((uint8_t *)str3, 8);
  Serial.println(fl.getFletcher());

  fl.begin();
  for (int i = 0; i < 8; i++) fl.add((uint8_t)str3[i]);
  Serial.println(fl.getFletcher());
}


void loop()
{
}


// -- END OF FILE --
