//
//    FILE: Adler_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo


#include "Arduino.h"
#include "Adler.h"


//  expected output
//  ADLER_LIB_VERSION: 0.1.1
//  5C801F0
//  81E0256
//  E000325
//  11E60398


char str1[24] = "abcde";
char str2[24] = "abcdef";
char str3[24] = "abcdefgh";
char str4[24] = "Wikipedia";   // example from Wikipedia page.


void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.print("ADLER_LIB_VERSION: ");
  Serial.println(ADLER_LIB_VERSION);

  Serial.println(adler32((uint8_t *) str1, 5), HEX);
  Serial.println(adler32((uint8_t *) str2, 6), HEX);
  Serial.println(adler32((uint8_t *) str3, 8), HEX);
  Serial.println(adler32((uint8_t *) str4, 9), HEX);
}


void loop()
{
}


// -- END OF FILE --
