//
//    FILE: I2Ckeypad_demo01.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/I2CKeyPad
//
//  HISTORY:
//  2019-10-01  0.0.1  initial version
//  2020-06-26  0.1.0  updated with lib
//  2021-05-06  0.2.0  updated with lib


//  PCF8574
//    pin p0-p3 rows
//    pin p4-p7 columns
//  4x4 or smaller keypad.


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
}


void loop()
{
  uint32_t now = millis();
  char keys[] = "123A456B789C*0#DNF";  // N = NoKey, F = Fail

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


// -- END OF FILE --

