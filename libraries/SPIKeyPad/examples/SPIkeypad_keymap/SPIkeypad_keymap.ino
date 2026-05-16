//
//    FILE: SPIkeypad_keymap.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo key mapping
//     URL: https://github.com/RobTillaart/SPIKeyPad
//
//  MCP23S08
//    pin p0-p3 rows
//    pin p4-p7 columns
//  4x4 or smaller keypad.


#include "SPIKeyPad.h"

constexpr uint8_t SELECT = 10;
constexpr uint8_t SDOUT = 11;    //  MOSI
constexpr uint8_t SDIN = 12;     //  MISO
constexpr uint8_t SCLOCK = 13;   //  CLK

SPIKeyPad keyPad(SELECT);
//  SPIKeyPad keyPad(SELECT, SDIN, SDOUT, SCLOCK, 0);

char keymap[19] = "123A456B789C*0#DNF";  //  N = NoKey, F = Fail


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
  keyPad.loadKeyMap(keymap);
}


void loop()
{
  if (keyPad.isPressed())
  {
    char ch = keyPad.getChar();     //  note we want the translated char
    int key = keyPad.getLastKey();
    Serial.print(key);
    Serial.print(" \t");
    Serial.println(ch);
    delay(100);
  }
}


//  -- END OF FILE --
