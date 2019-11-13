//
//    FILE: MCP23017_test.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2019-10-14
//
// PUPROSE: test MCP23017 library
//

#include "MCP23017.h"
#include <Wire.h>

MCP23017 MCP(0x27);

void setup()
{
  Serial.begin(230400);
  Serial.print("MCP23017_test version: ");
  Serial.println(MCP23017_LIB_VERSION);

  Wire.begin();

  MCP.begin();

  MCP.pinMode8(0, 0x00);  // 0 = output , 1 = input
  MCP.pinMode8(1, 0x00);
  Wire.setClock(50);

  Serial.println("TEST digitalWrie(0)");
  for (int i = 0; i < 16; i++)
  {
    MCP.digitalWrite(0, i % 2);  // alternating HIGH/LOW
    Serial.print(i % 2);
    Serial.print('\t');
    delay(250);
  }
  Serial.println();
  Serial.println();

  Serial.println("TEST digitalWrie(pin)");
  for (int pin = 0; pin < 16; pin++)
  {
    MCP.digitalWrite(pin, 1 - pin % 2); // alternating HIGH/LOW
    Serial.print(1 - pin % 2);
    Serial.print('\t');
  }
  Serial.println();
  Serial.println();

  Serial.println("TEST read back");

  for (int pin = 0; pin < 16; pin++)
  {
    int val = MCP.digitalRead(pin);
    Serial.print(val);
    Serial.print('\t');
  }
  Serial.println();
  Serial.println();
}

void loop()
{
}

// -- END OF FILE --