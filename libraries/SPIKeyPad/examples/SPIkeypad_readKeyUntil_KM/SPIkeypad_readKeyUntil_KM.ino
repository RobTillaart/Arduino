//
//    FILE: SPIkeypad_readKeyUntil_KM.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo reading until specific keyPress - using build in key mapping
//     URL: https://github.com/RobTillaart/SPIKeyPad
//
//  MCP23S08
//    pin p0-p3 rows
//    pin p4-p7 columns
//  4x4 or smaller keypad.
//
//  This demo doesn't use the build in key mapping.

#include "SPIKeyPad.h"

constexpr uint8_t SELECT = 10;
constexpr uint8_t SDOUT = 11;    //  MOSI
constexpr uint8_t SDIN = 12;     //  MISO
constexpr uint8_t SCLOCK = 13;   //  CLK

SPIKeyPad keyPad(SELECT);
//  SPIKeyPad keyPad(SELECT, SDIN, SDOUT, SCLOCK, 0);

char keymap[19] = "123A456B789C*0#DNF";     //  ... NoKey  Fail }


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SPI_KEYPAD_LIB_VERSION: ");
  Serial.println(SPI_KEYPAD_LIB_VERSION);
  Serial.println();

  if (keyPad.usesHWSPI())
  {
    SPI.begin();
  }

  if (keyPad.begin() == false)
  {
    Serial.println("Could not initialize");
  }

  keyPad.loadKeyMap(keymap);
}


void loop()
{
  char buf[20];
  int result = readKeyPadUntil('#', buf, 20, 10000);
  if (result == 0)
  {
    Serial.print("SUCCESS: ");
    Serial.println(buf);
  }
  if (result == -1)
  {
    Serial.print("FAILURE: ");
    Serial.println(buf);
  }
  if (result == -2)
  {
    Serial.print("TIMEOUT: ");
    Serial.println(buf);
  }
  if (result == -3)
  {
    Serial.print("OVERFLW: ");
    Serial.println(buf);
  }
}


//  until   = end character
//  buffer  = buffer to fill
//  length  = length of buffer (including '\0'
//  timeout = timeout in milliseconds
//  returns 0 = success
//         -1 = keyPad fail
//         -2 = timeout
//         -3 = buffer overflow
//
int readKeyPadUntil(char until, char * buffer, uint8_t length, uint16_t timeout)
{
  uint8_t bufferIndex = 0;
  uint32_t start = millis();

  //  empty the return buffer
  buffer[bufferIndex] = 0;

  while (true)
  {
    char ch = 0;
    //  wait for keypress
    while ((ch = keyPad.getChar()) == 'N')
    {
      if (millis() - start > timeout) return -2;
    }
    //  wait for release
    while (ch == keyPad.getChar())
    {
      delay(10);
      if (millis() - start > timeout) return -2;
    }
    if (ch == 'F')   return -1;
    if (ch == until) return 0;
    if ( bufferIndex == length ) return -3;  //  overflow
    //  add key to buffer
    buffer[bufferIndex++] = ch;
    buffer[bufferIndex]   = 0;

    yield();
  }
  return -1;
}


//  -- END OF FILE --
