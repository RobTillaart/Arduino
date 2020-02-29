//
//    FILE: binhex_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2020-02-29
//    (c) : -
//

#include "MathHelpers.h"

uint16_t x = 15;

void setup()
{
  Serial.begin(115200);
  for (uint8_t digits = 1; digits < 9; digits += 2)
  {
    Serial.println(hex(x, digits));
  }
  Serial.println();

  Serial.println(hex(12345, 4));
  Serial.println();

  for (int i = 0; i < 10; i++)
  {
    uint32_t z = random(4E9);
    Serial.print(hex(z));
    Serial.print('\t');
    Serial.println(z, HEX);
  }
  Serial.println();
  
  for (int i = 0; i < 10; i++)
  {
    uint8_t z = random(256);
    Serial.print(bin(z));
    Serial.print('\t');
    Serial.println(z, BIN);
  }
  Serial.println();

  for (int i = 0; i < 10; i++)
  {
    uint8_t z = random(256);
    Serial.print(bin(z, 4));
    Serial.print('\t');
    Serial.println(z, BIN);
  }
  Serial.println();

  
  Serial.println(bin(-5));
  Serial.println(hex(-16));
}

void loop()
{

}