//
//    FILE: I2Ckeypad_demo02.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
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

    bool connected  = keyPad.isConnected();
    bool pressed    = keyPad.isPressed();
    uint8_t lastKey = keyPad.getLastKey();

    start = micros();
    uint8_t index = keyPad.getKey();
    stop = micros();
    Serial.print(millis());
    Serial.print("\t");
    Serial.print(index);
    Serial.print("\t");
    Serial.print((char)"123A456B789C*0#DNF"[index]);  //  NoKey, Fail
    Serial.print("\t");
    Serial.print(lastKey);
    Serial.print("\t");
    Serial.print(pressed ? "True" : "False");
    Serial.print("\t");
    Serial.print(connected ? "True" : "False");
    Serial.print("\t");
    Serial.println(stop - start);
  }
}


//  -- END OF FILE --

