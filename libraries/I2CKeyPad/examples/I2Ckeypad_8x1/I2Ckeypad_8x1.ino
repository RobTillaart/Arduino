//
//    FILE: I2Ckeypad_8x1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo 8x1 or smaller keypad
//     URL: https://github.com/RobTillaart/I2CKeyPad
//
//  PCF8574
//    pin p0-p7 rows


#include "Wire.h"
#include "I2CKeyPad.h"

const uint8_t KEYPAD_ADDRESS = 0x38;

I2CKeyPad keyPad(KEYPAD_ADDRESS);

uint32_t start, stop;
uint32_t lastKeyPressed = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();
  Wire.setClock(400000);
  if (keyPad.begin() == false)
  {
    Serial.println("\nERROR: cannot communicate to keypad.\nPlease reboot.\n");
    while(1);
  }

  keyPad.setKeyPadMode(I2C_KEYPAD_8x1);
}


void loop()
{
  uint32_t now = millis();
  //  adjust keymap if needed
  char keys[] = "12345678        NF";  //  N = NoKey, F = Fail

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
