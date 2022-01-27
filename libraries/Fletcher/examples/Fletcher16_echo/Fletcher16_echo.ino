//
//    FILE: Fletcher16_echo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: echo's Fletcher checksum after every character.

#include "Arduino.h"
#include "Fletcher16.h"

Fletcher16 fl;


void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.println("Fletcher16_echo");

  fl.begin();
}


void loop()
{
  if (Serial.available())
  {
    uint8_t c = Serial.read();
    fl.add(c);
    Serial.print(c);
    Serial.print("\t");
    Serial.println(fl.getFletcher());
  }
}


// -- END OF FILE --
