//
//    FILE: I2Ckeypad_readKeyUntil_KM.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo reading until specific keyPress - using build in key mapping
//     URL: https://github.com/RobTillaart/I2CKeyPad
//
//  PCF8574
//    pin p0-p3 rows
//    pin p4-p7 columns
//  4x4 or smaller keypad.
//
//  This demo doesn't use the build in key mapping.


#include "Wire.h"
#include "I2CKeyPad.h"


const uint8_t KEYPAD_ADDRESS = 0x38;

I2CKeyPad keyPad(KEYPAD_ADDRESS);

char keymap[19] = "123A456B789C*0#DNF";     // ... NoKey  Fail }


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
  keyPad.loadKeyMap(keymap);
}


void loop()
{
  char buf[20];
  int result = readKeyPadUntil('#', buf, 20, 10000);
  if (result == 0)
  {
    Serial.print("SUCCESS: ");
    Serial.println(buf);
  }
  if (result == -1)
  {
    Serial.print("FAILURE: ");
    Serial.println(buf);
  }
  if (result == -2)
  {
    Serial.print("TIMEOUT: ");
    Serial.println(buf);
  }
  if (result == -3)
  {
    Serial.print("OVERFLW: ");
    Serial.println(buf);
  }
}


//  until   = end character
//  buffer  = buffer to fill
//  length  = length of buffer (including '\0'
//  timeout = timeout in milliseconds
//  returns 0 = success
//         -1 = keyPad fail
//         -2 = timeout
//         -3 = buffer overflow
//
int readKeyPadUntil(char until, char * buffer, uint8_t length, uint16_t timeout)
{
  uint8_t bufferIndex = 0;
  uint32_t start = millis();
  char lastChar = '\0';

  // empty the return buffer
  buffer[bufferIndex] = 0;

  while (millis() - start < timeout)
  {
    char ch = keyPad.getChar();
    if (ch == 'N')        lastChar = 'N';
    else if (ch == until) return 0;       //  success
    else if (ch == 'F')   return -1;      //  keyPad fail
    else
    {
      if (ch != lastChar)
      {
        lastChar = ch;
        if ( bufferIndex == length ) return -3;  //  overflow
        //  add key to buffer
        buffer[bufferIndex++] = ch;
        buffer[bufferIndex]   = 0;
      }
    }
    yield();
  }
  return -2;    //  timeout
}


//  -- END OF FILE --

