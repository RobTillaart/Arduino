//    FILE: luhn_isValid.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/LUHN


#include "Arduino.h"
#include "LUHN.h"


uint32_t start, stop;

LUHN checker;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);

  //  example https://en.wikipedia.org/wiki/Luhn_algorithm
  test("79927398713");
  test("49927398716");
  test("49927398717");       // false
  test("1234567812345671");
  test("1234567812345670");  // false
  test("371449635398431");
}


void loop()
{
}


void test(char * nr)
{
  delay(10);
  start = micros();
  bool b = checker.isValid(nr);
  stop = micros();
  Serial.print("VALID:\t");
  Serial.println(b);
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  Serial.println();

}

//  -- END OF FILE --
