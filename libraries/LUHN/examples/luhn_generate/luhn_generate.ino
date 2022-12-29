//    FILE: luhn_generate.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2022-12-24
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
  //  Serial.print((1.0*(stop - start))/ strlen(number));  per digit
  Serial.print("\t");
  Serial.println(number);
  delay(100);
}


//  -- END OF FILE --
