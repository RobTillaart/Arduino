//
//    FILE: demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: search the longest palindrome
//     URL: https://github.com/RobTillaart/


#include "Arduino.h"
#include "palindrome.h"

palindrome pd;


uint32_t start, stop;

#define PLEN  1600
char str[PLEN];




void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PALINDROME_LIB_VERSION: ");
  Serial.println(PALINDROME_LIB_VERSION);
  Serial.println();
  delay(100);

  for (int i = 0; i < PLEN - 1; i++)
  {
    str[i] = 'a' + random(4);
  }
  str[PLEN - 1] = 0;

  //  Serial.println(str);
  //  delay(100);

  int position = 0;
  int length = 0;
  start = micros();
  pd.findOddPalindrome(str, position, length);
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  printPartial(str, position, length);
  Serial.println();
  delay(100);

  start = micros();
  pd.findEvenPalindrome(str, position, length);
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  printPartial(str, position, length);
  Serial.println();
  delay(100);

  start = micros();
  pd.findPalindrome(str, position, length);
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  printPartial(str, position, length);
  Serial.println();
  delay(100);

  Serial.println("done...");
}


void loop()
{
}


void printPartial(char * str, int pos, int len)
{
  Serial.print(pos);
  Serial.print("\t");
  Serial.print(len);
  Serial.print("\t");
  for (int a = pos; a < pos + len; a++) Serial.print(str[a]);
  Serial.println();
}

//  -- END OF FILE --
