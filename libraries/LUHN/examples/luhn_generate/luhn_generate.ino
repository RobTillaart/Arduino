//    FILE: luhn_generate.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/LUHN


#include "Arduino.h"
#include "LUHN.h"


uint32_t start, stop;

LUHN checker;

char number[50];


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LUHN_LIB_VERSION: ");
  Serial.println(LUHN_LIB_VERSION);
  Serial.println();
  delay(10);
}


void loop()
{
  start = micros();
  bool b = checker.generate(number, 26, (char *)"1234");
  stop = micros();
  Serial.print(b);
  Serial.print("\t");
  Serial.print(checker.isValid(number));
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print((1.0 * (stop - start)) / strlen(number));  //  per digit
  Serial.print("\t");
  Serial.println(number);
  delay(100);
}


//  -- END OF FILE --
