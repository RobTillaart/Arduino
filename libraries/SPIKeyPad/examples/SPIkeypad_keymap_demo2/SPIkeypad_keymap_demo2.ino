//
//    FILE: I2Ckeypad_keymap_demo2.ino
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



//  two different lay out styles of a numeric keyPad
char phone_layout[19]      = "123A456B789C*0#DNF";  //  N = NoKey, F = Fail
char calculator_layout[19] = "789A456B123C*0#DNF";  //  N = NoKey, F = Fail


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

  keyPad.loadKeyMap(phone_layout);
}


void loop()
{
  if (keyPad.isPressed())
  {
    char ch = keyPad.getChar();
    Serial.print("CH : ");
    Serial.println(ch);
    if (ch == '*')
    {
      keyPad.loadKeyMap(phone_layout);
    }
    if (ch == '#')
    {
      keyPad.loadKeyMap(calculator_layout);
    }
  }
  delay(100);
}


//  -- END OF FILE --
