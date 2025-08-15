//
//    FILE: Adler_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/Adler


#include "Arduino.h"
#include "Adler.h"
#include "printHelpers.h"


//  expected output
//  ADLER_LIB_VERSION: 0.3.0
//
//  E1F5
//  4660
//  4634
//  40A7
//
//  5C801F0
//  81E0256
//  E000325
//  11E60398
//
//  000005C8000001F0
//  0000081E00000256
//  00000E0000000325
//  000011E600000398
//
//  note: difference between the adler32 and the adler64 == extra zero's
//        as the strings are very small.


char str1[24] = "abcde";
char str2[24] = "abcdef";
char str3[24] = "abcdefgh";
char str4[24] = "Wikipedia";   //  example from Wikipedia page.


void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ADLER_LIB_VERSION: ");
  Serial.println(ADLER_LIB_VERSION);
  Serial.println();

  Serial.println(adler16((uint8_t *) str1, 5), HEX);
  Serial.println(adler16((uint8_t *) str2, 6), HEX);
  Serial.println(adler16((uint8_t *) str3, 8), HEX);
  Serial.println(adler16((uint8_t *) str4, 9), HEX);
  Serial.println();

  Serial.println(adler32((uint8_t *) str1, 5), HEX);
  Serial.println(adler32((uint8_t *) str2, 6), HEX);
  Serial.println(adler32((uint8_t *) str3, 8), HEX);
  Serial.println(adler32((uint8_t *) str4, 9), HEX);
  Serial.println();

  Serial.println(hex(adler64((uint8_t *) str1, 5)));
  Serial.println(hex(adler64((uint8_t *) str2, 6)));
  Serial.println(hex(adler64((uint8_t *) str3, 8)));
  Serial.println(hex(adler64((uint8_t *) str4, 9)));
  Serial.println();

  Serial.println(adler16(str1, 5), HEX);
  Serial.println(adler16(str2, 6), HEX);
  Serial.println(adler16(str3, 8), HEX);
  Serial.println(adler16(str4, 9), HEX);
  Serial.println();

  Serial.println(adler32(str1, 5), HEX);
  Serial.println(adler32(str2, 6), HEX);
  Serial.println(adler32(str3, 8), HEX);
  Serial.println(adler32(str4, 9), HEX);
  Serial.println();

  Serial.println(hex(adler64(str1, 5)));
  Serial.println(hex(adler64(str2, 6)));
  Serial.println(hex(adler64(str3, 8)));
  Serial.println(hex(adler64(str4, 9)));
  Serial.println();
}


void loop()
{
}


//  -- END OF FILE --
