//
//    FILE: MCP4725_keypad.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: test MCP4725 lib
//    DATE: 2019-10-16
//     URL: https://github.com/RobTillaart/MCP4725
//

// Note: possible to replace I2CKeypad with Serial code

#include "Wire.h"
#include "MCP4725.h"

MCP4725 MCP(0x62);  // 0x62 or 0x63

#include "I2CKeyPad.h"
#define KEYPAD_ADDR 0x38

I2CKeyPad keyPad;

uint32_t value = 0;
uint32_t oldValue = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Serial.println(MCP4725_VERSION);

  MCP.begin();
  MCP.setValue(0);
  keyPad.begin(KEYPAD_ADDR);
}

void loop()
{
  char c = updateKeyPadValue(value, 4095);
  if (c == '#')
  {
    MCP.setValue(value);
  }
  if (value != oldValue)
  {
    Serial.println(value);
    oldValue = value;
  }
}


char updateKeyPadValue(uint32_t &value, uint32_t maxValue)
{
  char v[19] = "123A456B789C*0#DNF";   // last 2 are Fail and Nokey
  static uint8_t lastKey = 0;

  uint8_t idx = keyPad.getKey();
  char c = v[idx];

  if (lastKey != c)
  {
    lastKey = c;
    switch (c)
    {
      case '0' ... '9':
        value *= 10;
        value += c - '0';
        break;
      case '*':
        if (value > 0) value /= 10;
        break;
      case 'C':
        value = 0;
        break;
      default:
        break;
    }
  }
  while (value > maxValue) value /= 10;
  return c;
}

// -- END OF FILE --
