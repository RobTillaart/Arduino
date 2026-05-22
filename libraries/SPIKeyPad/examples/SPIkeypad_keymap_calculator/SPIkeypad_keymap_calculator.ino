//
//    FILE: SPIkeypad_keymap_calculator.ino
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

// minimal calculator layout
//  char calculator_layout[19] = "789+456-123  0  NF";  //  N = NoKey, F = Fail
char calculator_layout[19] = "123+456-789  0  NF";  //  N = NoKey, F = Fail
int32_t sum = 0;
int32_t val = 0;


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

  keyPad.loadKeyMap(calculator_layout);
}


void loop()
{
  if (keyPad.isPressed())
  {
    char ch = keyPad.getChar();
    switch (ch)
    {
      case '0'...'9' :
        val = val * 10 + ch - '0';
        Serial.print(ch);
        break;
      case '+':
        Serial.print(" +");
        sum += val;
        val = 0;
        Serial.print("\nSUM: ");
        Serial.println(sum);
        break;
      case '-' :
        Serial.print(" -");
        sum -= val;
        val = 0;
        Serial.print("\nSUM: ");
        Serial.println(sum);
        break;
    }
  }
  delay(100);
}


//  -- END OF FILE --
