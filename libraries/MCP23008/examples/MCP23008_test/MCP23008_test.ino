//
//    FILE: MCP23008_test.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2023-06-20
// PUPROSE: test MCP23008 library


#include "MCP23008.h"
#include "Wire.h"

MCP23008 MCP(0x22);

void setup()
{
  Serial.begin(115200);
  Serial.print("MCP23008_test version: ");
  Serial.println(MCP23008_LIB_VERSION);

  Wire.begin();
  MCP.begin();

  test_pin_mode();
  test_digital_read();
}


void test_pin_mode()
{
  MCP.pinMode8(0x00);    // 0 = output , 1 = input
  uint8_t value = MCP.getPinMode8();
  Serial.println(value, HEX);

  MCP.pinMode8(0xFF);
  value = MCP.getPinMode8();
  Serial.println(value, HEX);

  Serial.println();
  for (int i = 0; i < 8; i++)
  {
    MCP.pinMode(i, OUTPUT);
    value = MCP.getPinMode8();
    Serial.println(value, HEX);
  }

  Serial.println();
  for (int i = 0; i < 8; i++)
  {
    MCP.pinMode(i, INPUT);
    value = MCP.getPinMode8();
    Serial.println(value, HEX);
  }

  Serial.println();
  for (int i = 0; i < 8; i++)
  {
    MCP.pinMode(i, OUTPUT);
    value = MCP.getPinMode8();
    Serial.println(value, HEX);
  }

  Serial.println();
  for (int i = 0; i < 8; i++)
  {
    MCP.pinMode(i, INPUT_PULLUP);
    value = MCP.getPinMode8();
    Serial.println(value, HEX);
  }

  Serial.println();
}


void test_digital_read()
{
  // set all lines to input
  MCP.pinMode8(0xFF);
  uint8_t value = MCP.getPinMode8();
  Serial.println(value, HEX);

  uint32_t start = millis();
  while (millis() - start < 60000)
  {
    for (int i = 0; i < 8; i++)
    {
      value = MCP.digitalRead(i);
      Serial.print(value, HEX);
    }
    Serial.println();
    delay(1000);
  }
}


void loop()
{
}


// -- END OF FILE --
