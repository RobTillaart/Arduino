//
//    FILE: demo_isPalindrome.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: search the longest palindrome
//     URL: https://github.com/RobTillaart/


#include "Arduino.h"
#include "palindrome.h"

palindrome pd;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PALINDROME_LIB_VERSION: ");
  Serial.println(PALINDROME_LIB_VERSION);
  Serial.println();
  delay(100);

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
