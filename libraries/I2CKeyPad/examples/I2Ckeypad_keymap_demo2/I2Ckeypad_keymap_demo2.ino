//
//    FILE: I2Ckeypad_keymap_demo2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo key mapping
//     URL: https://github.com/RobTillaart/I2CKeyPad
//
//  PCF8574
//    pin p0-p3 rows
//    pin p4-p7 columns
//  4x4 or smaller keypad.


#include "Wire.h"
#include "I2CKeyPad.h"


const uint8_t KEYPAD_ADDRESS = 0x38;

I2CKeyPad keyPad(KEYPAD_ADDRESS);


// two different lay out styles of a nummeric keyPad
char phone_layout[19]      = "123A456B789C*0#DNF";  //  N = NoKey, F = Fail
char calculator_layout[19] = "789A456B123C*0#DNF";  //  N = NoKey, F = Fail


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

  keyPad.loadKeyMap(phone_layout);
}


void loop()
{
  if (keyPad.isPressed())
  {
    int ch = keyPad.getChar();
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
}


//  -- END OF FILE --

