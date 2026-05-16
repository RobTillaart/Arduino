//    FILE: SPIKeyPad_4x4.ino
//  AUTHOR: Rob Tillaart, Chris0xdeadbeef
// PURPOSE: demo 4x4 keypad
//     URL: https://github.com/RobTillaart/SPIKeyPad
//
//  MCP23S08 (SPI)
//    GP0–GP3 rows
//    GP4–GP7 columns

#include "SPIKeyPad.h"

constexpr uint8_t SELECT = 10;
constexpr uint8_t SDOUT = 11;    //  MOSI
constexpr uint8_t SDIN = 12;     //  MISO
constexpr uint8_t SCLOCK = 13;   //  CLK

SPIKeyPad keyPad(SELECT);
//  SPIKeyPad keyPad(SELECT, SDIN, SDOUT, SCLOCK, 0);

uint32_t start, stop;
uint32_t lastKeyPressed = 0;


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

  keyPad.setKeyPadMode(SPI_KEYPAD_4x4);
}


void loop()
{
  uint32_t now = millis();
  //  adjust keyMap if needed
  char keys[] = "1234567890ABCDE NF";  //  N = NoKey, F = Fail

  if (now - lastKeyPressed >= 100)
  {
    lastKeyPressed = now;

    start = micros();
    uint8_t index = keyPad.getKey();
    stop = micros();

    Serial.print(millis());
    Serial.print("\t");
    Serial.print(index);
    Serial.print("\t");
    Serial.print(keys[index]);
    Serial.print("\t");
    Serial.println(stop - start);
  }
}


//  -- END OF FILE --
