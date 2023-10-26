//    FILE: luhn_check.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/LUHN


#include "Arduino.h"
#include "LUHN.h"


uint32_t start, stop;

LUHN checker;

//  example https://en.wikipedia.org/wiki/Luhn_algorithm
char cardNumber[20] = "79927398713";


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LUHN_LIB_VERSION: ");
  Serial.println(LUHN_LIB_VERSION);

  //  SHOULD PRINT 3
  Serial.println(checker.generateChecksum((char *)"7992739871"));
  //  SHOULD PRINT 0
  Serial.println(checker.generateChecksum((char *)""));
}

void loop()
{
  char buffer[50] = "";
  int len = 0;
  Serial.println("give string");

  while (buffer[len - 1] != '\n')
  {
    if (Serial.available())
    {
      buffer[len++] = Serial.read();
      buffer[len] = '\0';
    }
  }
  Serial.print(buffer);
  Serial.print(" ==> ");
  Serial.println(checker.generateChecksum(buffer));
}


// -- END OF FILE --
