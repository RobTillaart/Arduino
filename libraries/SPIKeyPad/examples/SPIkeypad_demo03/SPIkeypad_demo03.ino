//
//    FILE: I2CKeyPad_demo03.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo reading a larger value from the keyPad
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

uint32_t start, stop;
uint32_t lastKeyPressed = 0;
uint32_t value = 0;

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
}


void loop()
{
  uint32_t now = millis();

  if (now - lastKeyPressed >= 100)
  {
    lastKeyPressed = now;

    start = micros();
    char c = handleKeyPadValue(value);
    if (value > 125000) value = 125000;  //  some sample max.
    stop = micros();
    Serial.print(millis());
    Serial.print("\t");
    Serial.print(value);
    Serial.print("\t");
    Serial.print((char) c);
    Serial.print("\t");
    Serial.println(stop - start);
  }
}


//  handleKeyPadValue is used to read a uint32_t from the keypad
//  every digit must be pressed separately
//  the last key pressed is also returned.
//
//  0..9 adds to the number
//  * means remove last digit
//  # resets to zero
//  ABCD are not mapped.
char handleKeyPadValue(uint32_t &value)
{
  char v[19] = "123A456B789C*0#DNF";  //  N = NoKey, F = Fail
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
      case '#':
        value = 0;
        break;
      case 'A' ... 'D':
        //  e.g. store value in EEPROM
        break;
      case 'F':
        Serial.println("FAIL");
        break;
      case 'N':
        Serial.println("NOKEY");
        break;
      default:
        break;
    }
  }
  return c;
}


//  -- END OF FILE --
