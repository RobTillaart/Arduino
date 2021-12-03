//
//    FILE: demo_isPalindrome.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: search the longest palindrome
//    DATE: 2021-12-03
//     URL: https://github.com/RobTillaart/


#include "Arduino.h"
#include "palindrome.h"

palindrome pd;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  test("");
  test("a");
  test("aa");
  test("aaa");
  test("aaaa");
  Serial.println();
  
  test("ab");
  test("aba");
  test("abaa");
  test("aabaa");
  test("abababa");
  Serial.println();

  test("11011");
  test("0011011");
  test("123");
  test("/*  */");
  test("##############");
  Serial.println();

  Serial.println("done...");
}


void loop()
{
}


void test(const char * str)
{
  bool b = pd.isPalindrome(str);
  Serial.print(str);
  Serial.println(b ? "\ttrue" : "\tfalse");
}



// -- END OF FILE --
