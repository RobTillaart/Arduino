//
//    FILE: I2Ckeypad_demo01.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/I2CKeyPad
//
// HISTORY:
// 2019-10-01 0.0.1 initial version
// 2020-06-26 0.1.0 updated with lib

// PCF8574
//    pin p0-p3 rows
//    pin p4-p7 colums
// 4x4 or smaller keypad.

#include "Wire.h"
#include "I2CKeyPad.h"

const uint8_t KEYPAD_ADDRESS = 0x38;

I2CKeyPad keyPad;

uint32_t start, stop;
uint32_t lastKeyPressed = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();
  Wire.setClock(400000);
  if (keyPad.begin(KEYPAD_ADDRESS) == false)
  {
    Serial.println("\nERROR: cannot communicate to keypad.\nPlease reboot.\n");
    while(1);
  }
}


void loop()
{
  uint32_t now = millis();
  char keys[] = "123A456B789C*0#DNF";  // N = Nokey, F = Fail

  if (now - lastKeyPressed >= 100)
  {
    lastKeyPressed = now;

    start = micros();
    uint8_t idx = keyPad.getKey();
    stop = micros();

    Serial.print(millis());
    Serial.print("\t");
    Serial.print(idx);
    Serial.print("\t");
    Serial.print(keys[idx]);
    Serial.print("\t");
    Serial.println(stop - start);
  }
}

// -- END OF FILE --
