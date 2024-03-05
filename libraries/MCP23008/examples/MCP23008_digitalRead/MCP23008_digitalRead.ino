//
//    FILE: MCP23008_digitalRead.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test MCP23008 library
//     URL: https://github.com/RobTillaart/MCP23008


#include "MCP23008.h"


MCP23008 MCP(0x27);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MCP23008_LIB_VERSION: ");
  Serial.println(MCP23008_LIB_VERSION);
  Serial.println();
  delay(100);

  Wire.begin();
  MCP.begin();

  Serial.print("Connect: ");
  Serial.println(MCP.isConnected());

  //  all at once.
  //  MCP.pinMode8(0xFF);
  //  set individual pins
  for (int pin = 0; pin < 8; pin++)
  {
    MCP.pinMode1(pin, INPUT);
  }
  Serial.println("TEST read1(pin)");
}


void loop()
{
  for (int pin = 0; pin < 8; pin++)
  {
    int val = MCP.read1(pin);
    Serial.print(val);
    Serial.print('\t');
  }
  Serial.println();
  delay(1000);
}


//  -- END OF FILE --
