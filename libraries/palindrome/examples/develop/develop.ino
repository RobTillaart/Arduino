//
//    FILE: develop.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: search the longest palindrome
//    DATE: 2021-12-02
//     URL: https://github.com/RobTillaart/


#include "Arduino.h"


uint32_t start, stop;

#define PLEN  1600
char str[PLEN];


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  for (int i = 0; i < PLEN - 1; i++)
  {
    str[i] = 'a' + random(4);
  }
  str[PLEN - 1] = 0;

  //Serial.println(str);
  // delay(100);

  int position = 0;
  int length = 0;
  start = micros();
  findOddPalindrome(str, position, length);
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  printPartial(str, position, length);
  Serial.println();
  delay(100);

  start = micros();
  findEvenPalindrome(str, position, length);
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  printPartial(str, position, length);
  Serial.println();
  delay(100);

  start = micros();
  findPalindrome(str, position, length);
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


int findPalindrome(const char * str, int &position, int &length)
{
  int posOdd = 0, lengthOdd = 0;
  int posEven = 0, lengthEven = 0;
  findOddPalindrome(str, posOdd, lengthOdd);
  findEvenPalindrome(str, posEven, lengthEven);
  if (lengthEven > lengthOdd)
  {
    position = posEven;
    length = lengthEven;
    return length;
  }
  position = posOdd;
  length = lengthOdd;
  return length;
}


int findEvenPalindrome(const char * str, int &position, int &length)
{
  int sl = strlen(str);
  if (sl == 0) return -1;

  int newpos = 0;
  int newlen = 1;
  for (int i = 0; i < sl; i++)
  {
    if (str[i] != str[i + 1]) continue;
    int j = i - 1;
    int k = i + 2;
    while (0 <= j && k < sl)
    {
      if (str[j] != str[k]) break;
      j--;
      k++;
    }
    int pos = j + 1;
    int len = k - j - 1;
    if (len > newlen)
    {
      newlen = len;
      newpos = pos;
      // printPartial(str, newpos, newlen);
    }
  }
  position = newpos;
  length = newlen;
  return length;
}


int findOddPalindrome(const char * str, int &position, int &length)
{
  int sl = strlen(str);
  if (sl == 0) return -1;

  int newpos = 0;
  int newlen = 1;
  for (int i = 1; i < sl; i++)
  {
    int j = i - 1;
    int k = i + 1;
    while (0 <= j && k < sl)
    {
      if (str[j] != str[k]) break;
      j--;
      k++;
    }
    int pos = j + 1;
    int len = k - j - 1;
    if (len > newlen)
    {
      newlen = len;
      newpos = pos;
      // printPartial(str, newpos, newlen);
    }
  }
  position = newpos;
  length = newlen;
  return length;
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

// -- END OF FILE --

