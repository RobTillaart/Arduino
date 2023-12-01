//
//    FILE: MCP23S08_digitalWrite.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2021-12-30
// PUPROSE: test MCP23017 library


#include "MCP23S08.h"
#include "SPI.h"

MCP23S08 MCP(10, 5, 6, 7);   //  SW SPI   address 0x00


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("MCP23S08_LIB_VERSION: ");
  Serial.println(MCP23S08_LIB_VERSION);
  Serial.println();
  delay(100);

  SPI.begin();
  bool b = MCP.begin();
  Serial.print("BEGIN: ");
  Serial.println(b ? "true" : "false");
  delay(100);

  MCP.pinMode8(0x00);  // 0 = output , 1 = input

  Serial.println("TEST digitalWrite(0)");
  delay(100);
  for (int i = 0; i < 8; i++)
  {
    MCP.digitalWrite(0, i % 2);  // alternating HIGH/LOW
    Serial.print(i % 2);
    Serial.print(' ');
    delay(100);
  }
  Serial.println();
  Serial.println();

  Serial.println("TEST digitalWrite(pin)");
  delay(100);
  for (int pin = 0; pin < 8; pin++)
  {
    MCP.digitalWrite(pin, 1 - pin % 2); // alternating HIGH/LOW
    Serial.print(1 - pin % 2);
    Serial.print(' ');
    delay(100);
  }
  Serial.println();
  Serial.println();

  Serial.println("TEST read back");

  for (int pin = 0; pin < 8; pin++)
  {
    int val = MCP.digitalRead(pin);
    Serial.print(val);
    Serial.print(' ');
    delay(100);
  }
  Serial.println();
  Serial.println();
}


void loop()
{
}


// -- END OF FILE --
