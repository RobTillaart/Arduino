//
//    FILE: SPIkeypad_readKeyUntil.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo reading until specific keyPress
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

  keyPad.begin();
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


//
//  until   = end character
//  buffer  = buffer to fill
//  length  = length of buffer (including '\0'
//  timeout = timeout in milliseconds
//  returns 0 = success
//         -1 = keyPad fail
//         -2 = timeout
//         -3 = buffer overflow
int readKeyPadUntil(char until, char * buffer, uint8_t length, uint16_t timeout)
{
  char keymap[19] = "123A456B789C*0#DNF";  // ... NoKey  Fail }
  uint8_t bufferIndex = 0;
  uint32_t start = millis();

  //  empty buffer
  buffer[bufferIndex] = 0;

  while (true)
  {
    //  while no key is pressed wait
    while (keymap[keyPad.getKey()] == 'N')
    {
      yield();
      if (millis() - start > timeout) return -2;
    }

    //  get the key pressed
    uint8_t raw = keyPad.getLastKey();

    //  process key pressed
    uint8_t key = keymap[raw];

    //  while key is pressed wait until released
    while (keymap[keyPad.getKey()] == key)
    {
      yield();
      if (millis() - start > timeout) return -2;
    }

    //  handle end conditions
    if ( key == until) return 0;
    if ( key == 'F') return -1;    //  failed to read;
    if (bufferIndex == length) return -3;

    //  add key to buffer
    buffer[bufferIndex++] = key;
    buffer[bufferIndex] = 0;
  }
}


//  -- END OF FILE --
