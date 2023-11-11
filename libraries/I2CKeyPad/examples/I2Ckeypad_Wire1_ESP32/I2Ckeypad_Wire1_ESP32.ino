//
//    FILE: I2Ckeypad_Wire1_ESP32.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo reading a larger value from the keyPad
//     URL: https://github.com/RobTillaart/I2CKeyPad
//
//  PCF8574
//    pin p0-p3 rows
//    pin p4-p7 columns
//  4x4 or smaller keypad.


#include "Wire.h"
#include "I2CKeyPad.h"

const uint8_t KEYPAD_ADDRESS = 0x38;

I2CKeyPad keyPad(KEYPAD_ADDRESS, &Wire1);

uint32_t start, stop;
uint32_t lastKeyPressed = 0;
uint32_t value = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire1.begin(22, 23);  //  adjust pins if needed
  Wire1.setClock(400000);
  if (keyPad.begin() == false)
  {
    Serial.println("\nERROR: cannot communicate to keypad.\nPlease reboot.\n");
    while(1);
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
