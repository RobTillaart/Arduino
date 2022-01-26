//
//    FILE: Fletcher_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo

#include "Arduino.h"
#include "Fletcher.h"
#include "printHelpers.h"  //  https://github.com/RobTillaart/printHelpers

//  expected output
//
//  FLETCHER_LIB_VERSION: 0.1.0
//  51440
//  8279
//  1575
//  4031760169
//  1448095018
//  3957429649
//  14467467625952928454
//  14467579776138987718
//  3543817411021686982


char str1[24] = "abcde";
char str2[24] = "abcdef";
char str3[24] = "abcdefgh";


void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.print("FLETCHER_LIB_VERSION: ");
  Serial.println(FLETCHER_LIB_VERSION);

  Serial.println(fletcher16((uint8_t *) str1, 5));
  Serial.println(fletcher16((uint8_t *) str2, 6));
  Serial.println(fletcher16((uint8_t *) str3, 8));

  Serial.println(fletcher32((uint16_t *) str1, 3));
  Serial.println(fletcher32((uint16_t *) str2, 3));
  Serial.println(fletcher32((uint16_t *) str3, 4));

  Serial.println(print64(fletcher64((uint32_t *) str1, 2)));
  Serial.println(print64(fletcher64((uint32_t *) str2, 2)));
  Serial.println(print64(fletcher64((uint32_t *) str3, 2)));
}


void loop()
{
}


// -- END OF FILE --
