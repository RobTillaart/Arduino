//
//    FILE: MCP23008_digitalWrite.ino
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

  MCP.pinMode8(0x00);  // 0 = output , 1 = input
  Wire.setClock(100000);

  Serial.println("TEST digitalWrite(0)");
  for (int i = 0; i < 8; i++)
  {
    MCP.digitalWrite(0, i % 2);  // alternating HIGH/LOW
    Serial.print(i % 2);
    Serial.print('\t');
    delay(250);
  }
  Serial.println();
  Serial.println();

  Serial.println("TEST digitalWrite(pin)");
  for (int pin = 0; pin < 8; pin++)
  {
    MCP.digitalWrite(pin, 1 - pin % 2); // alternating HIGH/LOW
    Serial.print(1 - pin % 2);
    Serial.print('\t');
  }
  Serial.println();
  Serial.println();

  Serial.println("TEST read back");

  for (int pin = 0; pin < 8; pin++)
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

