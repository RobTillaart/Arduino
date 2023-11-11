//
//    FILE: I2Ckeypad_keymap_calculator.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo key mapping
//     URL: https://github.com/RobTillaart/I2CKeyPad
//
//  PCF8574
//    pin p0-p3 rows
//    pin p4-p7 columns
//  4x4 or smaller keypad.
//


#include "Wire.h"
#include "I2CKeyPad.h"


const uint8_t KEYPAD_ADDRESS = 0x38;

I2CKeyPad keyPad(KEYPAD_ADDRESS);

// minimal calculator layout
char calculator_layout[19] = "789+456-123  0  NF";  //  N = NoKey, F = Fail
int32_t sum = 0;
int32_t val = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();
  Wire.setClock(400000);
  if (keyPad.begin() == false)
  {
    Serial.println("\nERROR: cannot communicate to keypad.\nPlease reboot.\n");
    while (1);
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
        val *= 10 + ch - '0';
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

}


//  -- END OF FILE --

