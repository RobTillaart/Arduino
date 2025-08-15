//
//    FILE: Adler64_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/Adler


#include "Arduino.h"
#include "Adler64.h"
#include "printHelpers.h"


//  expected output
//  Adler64_test
//  ADLER64_LIB_VERSION: 0.3.0
//  000006F900000272
//  000006FE00000273
//  000006FA00000273



Adler64 ad;

uint8_t arr1[5]  = { 100, 120, 130, 135, 140 };
uint8_t arr2[5]  = { 101, 120, 130, 135, 140 };  //  minimal diff.
uint8_t arr3[5]  = { 100, 120, 130, 135, 141 };  //  minimal diff.


void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.println("Adler64_test");
  Serial.print("ADLER64_LIB_VERSION: ");
  Serial.println(ADLER64_LIB_VERSION);
  Serial.println();

  ad.begin();
  ad.add(arr1, 5);
  Serial.println(hex(ad.getAdler()));

  ad.begin();
  ad.add(arr2, 5);
  Serial.println(hex(ad.getAdler()));

  ad.begin();
  ad.add(arr3, 5);
  Serial.println(hex(ad.getAdler()));
}


void loop()
{
}


//  -- END OF FILE --
