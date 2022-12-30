//    FILE: luhn_check_stream.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2022-12-29
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/LUHN


#include "Arduino.h"
#include "LUHN.h"


uint32_t start, stop;

LUHN checker;

//  example https://en.wikipedia.org/wiki/Luhn_algorithm
char ID[20] = "79927398713";

char c;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);

  Serial.println("run I: debug");
  for (uint8_t i = 0; i < strlen(ID) - 1; i++)
  {
    c = checker.add(ID[i]);
    //  debug info
    Serial.print(ID[i]);
    Serial.print('\t');
    Serial.print(c);     //  should print 3 as last digit.
    Serial.println();
  }
  checker.reset();
  Serial.println();
  delay(10);

  start = micros();
  for (uint8_t i = 0; i < strlen(ID) - 1; i++)
  {
    checker.add(ID[i]);
  }
  c = checker.reset();
  stop = micros();
  Serial.println();
  Serial.print("run II:\t");
  Serial.println(c);     //  should also print 3 .
  Serial.print("  time:\t");
  Serial.print(stop - start);
  Serial.println();

  Serial.println("\ndone...");
}

void loop()
{

}


// -- END OF FILE --
