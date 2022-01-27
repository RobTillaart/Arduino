//
//    FILE: Fletcher16_restart.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo

#include "Arduino.h"
#include "Fletcher16.h"
#include "printHelpers.h"  //  https://github.com/RobTillaart/printHelpers

//  expected output
//  Fletcher16_restart
//  51440
//  51440
//  8279
//  8279
//  1575
//  1575

Fletcher16 fl;

char str[32] = "abcdefghijklmnopqrstuvwxyz";

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.println("Fletcher16_restart");

  Serial.println("\n add array 0..4");
  fl.begin();
  fl.add((uint8_t *)str, 5);
  uint16_t x = fl.getFletcher();
  Serial.println(x);

  Serial.println("\n add array 5..9");
  fl.add((uint8_t *)&str[5], 5);
  Serial.println(fl.getFletcher());
  
  Serial.println("\n array 0..9");
  fl.begin();
  fl.add((uint8_t *)str, 10);
  Serial.println(fl.getFletcher());
  
  Serial.println("\nrestart from position 5");
  fl.begin(x & 0xFF, x >> 8);     // split into s1 and s2;
  fl.add((uint8_t *)&str[5], 5);
  Serial.println(fl.getFletcher());
}


void loop()
{
}


// -- END OF FILE --
