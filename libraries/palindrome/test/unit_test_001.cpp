//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-12-02
// PURPOSE: unit tests for the palindrome library
//          https://github.com/RobTillaart/palindrome
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)


#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "palindrome.h"


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  fprintf(stderr, "PALINDROME_LIB_VERSION: %s\n", (char *) PALINDROME_LIB_VERSION);

  palindrome pd;
  int position;
  int length;
  char str[1000];


  for (int i = 0; i < 1000; i++)
  {
    str[i] = 'a' + random(1);
  }
  str[999] = 0;
  pd.findPalindrome(str, position, length);
  fprintf(stderr, "POS: %d   LEN: %d\n", position, length);


  for (int i = 0; i < 1000; i++)
  {
    str[i] = 'a' + random(2);
  }
  str[999] = 0;
  pd.findPalindrome(str, position, length);
  fprintf(stderr, "POS: %d   LEN: %d\n", position, length);


  for (int i = 0; i < 1000; i++)
  {
    str[i] = 'a' + random(3);
  }
  str[999] = 0;
  pd.findPalindrome(str, position, length);
  fprintf(stderr, "POS: %d   LEN: %d\n", position, length);


  for (int i = 0; i < 1000; i++)
  {
    str[i] = 'a' + random(4);
  }
  str[999] = 0;
  pd.findPalindrome(str, position, length);
  fprintf(stderr, "POS: %d   LEN: %d\n", position, length);


  for (int i = 0; i < 1000; i++)
  {
    str[i] = 'a' + random(5);
  }
  str[999] = 0;
  pd.findPalindrome(str, position, length);
  fprintf(stderr, "POS: %d   LEN: %d\n", position, length);
}


unittest(test_isPalindrome)
{
  palindrome pd;

  assertFalse(pd.isPalindrome(NULL));
  assertFalse(pd.isPalindrome(""));
  assertTrue(pd.isPalindrome("a"));
  assertTrue(pd.isPalindrome("aa"));
  assertTrue(pd.isPalindrome("aba"));
  assertFalse(pd.isPalindrome("aab"));
}


unittest(test_count)
{
  palindrome pd;
  char str[1000];
  for (int i = 0; i < 1000; i++)
  {
    str[i] = 'a' + random(1);
  }
  str[999] = 0;
  int length = pd.palindromeCount(str);
  float perc = pd.palindromePercentage(str);
  fprintf(stderr, "LEN: %d  PERC: %f\n", length, perc);


  for (int i = 0; i < 1000; i++)
  {
    str[i] = 'a' + random(2);
  }
  str[999] = 0;
  length = pd.palindromeCount(str);
  perc = pd.palindromePercentage(str);
  fprintf(stderr, "LEN: %d  PERC: %f\n", length, perc);


  for (int i = 0; i < 1000; i++)
  {
    str[i] = 'a' + random(3);
  }
  str[999] = 0;
  length = pd.palindromeCount(str);
  perc = pd.palindromePercentage(str);
  fprintf(stderr, "LEN: %d  PERC: %f\n", length, perc);


  for (int i = 0; i < 1000; i++)
  {
    str[i] = 'a' + random(4);
  }
  str[999] = 0;
  length = pd.palindromeCount(str);
  perc = pd.palindromePercentage(str);
  fprintf(stderr, "LEN: %d  PERC: %f\n", length, perc);


  for (int i = 0; i < 1000; i++)
  {
    str[i] = 'a' + random(5);
  }
  str[999] = 0;
  length = pd.palindromeCount(str);
  perc = pd.palindromePercentage(str);
  fprintf(stderr, "LEN: %d  PERC: %f\n", length, perc);
}


unittest_main()


// -- END OF FILE --
