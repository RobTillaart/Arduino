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

  Serial.print("Connect: ");
  Serial.println(MCP.isConnected());

  //  all at once.
  //  MCP.pinMode8(0xFF);
  //  set individual pins
  for (int pin = 0; pin < 8; pin++)
  {
    MCP.pinMode(pin, INPUT);
  }
  Serial.println("TEST digitalRead(pin)");
}

void loop()
{
  for (int pin = 0; pin < 8; pin++)
  {
    int val = MCP.digitalRead(pin);
    Serial.print(val);
    Serial.print('\t');
  }
  Serial.println();
  delay(1000);
}


//  -- END OF FILE --
