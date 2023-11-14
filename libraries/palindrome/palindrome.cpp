//
//    FILE: palindrome.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: Arduino library to do palindrome experiments.
//     URL: https://github.com/RobTillaart/palindrome


#include "palindrome.h"


palindrome::palindrome()
{
}


bool palindrome::isPalindrome(const char * str)
{
  if (str == NULL) return false;
  int sl = strlen(str);
  if (sl == 0) return false;

  int j = 0;
  int k = sl - 1;
  bool palin = (str[j++] == str[k--]);
  while (palin & ( j < k ))
  {
    palin = (str[j++] == str[k--]);
  }

  return palin;
}


int palindrome::findPalindrome(const char * str, int & position, int & length)
{
  if (str == NULL) return 0;
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


int palindrome::findEvenPalindrome(const char * str, int & position, int & length)
{
  if (str == NULL) return 0;
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
    }
  }
  position = newpos;
  length = newlen;
  return length;
}


int palindrome::findOddPalindrome(const char * str, int & position, int & length)
{
  if (str == NULL) return 0;
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
    }
  }
  position = newpos;
  length = newlen;
  return length;
}


int palindrome::palindromeCount(const char * str)
{
  if (str == NULL) return 0;
  int sl = strlen(str);
  if (sl == 0) return 0;

  int j = 0;
  int k = sl - 1;
  int count = 0;
  while (j <= k)
  {
    if (str[j++] == str[k--]) count++;
  }

  return count;
}


float palindrome::palindromePercentage(const char * str)
{
  if (str == NULL) return 0;
  int sl = strlen(str);
  if (sl == 0) return 0;
  if (sl % 2 == 1) sl++;  //  correction for odd length strings
  return (200.0 * palindromeCount(str)) / sl;
}


//  -- END OF FILE --

