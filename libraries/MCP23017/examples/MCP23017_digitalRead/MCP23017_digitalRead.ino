//
//    FILE: MCP23017_test.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2019-10-14
//
// PUPROSE: test MCP23017 library
//

#include "MCP23017.h"
#include <Wire.h>

MCP23017 MCP(0x38);

void setup()
{
  Serial.begin(230400);
  Serial.print("MCP23017_test version: ");
  Serial.println(MCP23017_LIB_VERSION);
  
  Wire.begin();
  MCP.begin();

  MCP.pinMode8(0, 0x00);   // CHECK
  MCP.pinMode8(1, 0x00);
  
  Serial.println("TEST digitalRead(pin)");
  for (int pin = 0; pin < 16; pin++)
  {
    int val = MCP.digitalRead(pin);
    Serial.print(val);
    Serial.print('\t');
  }
  Serial.println(); 
}

void loop()
{
}




