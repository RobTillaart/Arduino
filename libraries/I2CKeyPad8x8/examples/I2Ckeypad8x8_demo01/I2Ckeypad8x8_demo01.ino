//
//    FILE: I2Ckeypad8x8_demo01.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal demo
//     URL: https://github.com/RobTillaart/I2CKeyPad
//
//  PCF8575
//    pin p0-p7 rows
//    pin p8-p15 columns
//  8x8 or smaller keypad.


#include "Wire.h"
#include "I2CKeyPad8x8.h"

const uint8_t KEYPAD_ADDRESS = 0x20;

I2CKeyPad8x8 keyPad(KEYPAD_ADDRESS);

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
}


void loop()
{
  uint32_t now = millis();

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
    Serial.println(stop - start);
  }
}


//  -- END OF FILE --
