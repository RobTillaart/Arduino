//
//    FILE: MCP23008_digitalRead.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2019-10-14
// PUPROSE: test MCP23008 library


#include "MCP23008.h"
#include "Wire.h"


MCP23008 MCP(0x27);

void setup()
{
  Serial.begin(230400);
  Serial.print("MCP23008_test version: ");
  Serial.println(MCP23008_LIB_VERSION);

  Wire.begin();
  MCP.begin();

  MCP.pinMode8(0x00);

  Serial.println("TEST digitalRead(pin)");
  for (int pin = 0; pin < 8; pin++)
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


// -- END OF FILE --
