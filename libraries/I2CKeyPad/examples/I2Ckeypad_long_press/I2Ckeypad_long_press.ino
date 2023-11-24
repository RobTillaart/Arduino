//
//    FILE: I2Ckeypad_long_press.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/I2CKeyPad
//          https://github.com/RobTillaart/I2CKeyPad/issues/17
//
//  PCF8574
//    pin p0-p3 rows
//    pin p4-p7 columns
//  4x4 or smaller keypad.


#include "Wire.h"
#include "I2CKeyPad.h"

const uint8_t KEYPAD_ADDRESS = 0x38;
I2CKeyPad keyPad(KEYPAD_ADDRESS);

uint32_t lastKeyChecked = 0;
uint32_t startKey = 0;
uint32_t interval = 100;  //  milliseconds.
//  keep previous key value to detect long keypresses.
uint8_t  prevKey = I2C_KEYPAD_NOKEY;


#define  SHORT_THRESHOLD     300
#define  MEDIUM_THRESHOLD    600
#define  LONG_THRESHOLD      1200


enum STATE
{
  PRESS        = 1,
  SHORT_PRESS,
  MEDIUM_PRESS,
  LONG_PRESS,
  RELEASE,
  NOKEY,
};
STATE state = NOKEY;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println("I2C_KEYPAD_LIB_VERSION: ");
  Serial.println(I2C_KEYPAD_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(400000);
  if (keyPad.begin() == false)
  {
    Serial.println("\nERROR: cannot communicate to keypad.\nPlease reboot.\n");
    while (1);
  }
}


void loop()
{
  uint32_t now = millis();
  char keys[] = "123A456B789C*0#DNF";  //  N = NoKey, F = Fail

  //  read the keypad every interval.
  if (now - lastKeyChecked >= interval)
  {
    lastKeyChecked = now;
    //  read the keypad
    uint8_t key = keyPad.getKey();
    switch (key)
    {
      case I2C_KEYPAD_FAIL: state = NOKEY;
        break;

      case I2C_KEYPAD_NOKEY:
        if (key == prevKey)
        {
          state = NOKEY;
        }
        else
        {
          //  note handles press at release time!
          handlePress(state);
          state = RELEASE;
        }
        break;

      default:
        if (key == prevKey)
        {
          if (now - startKey < SHORT_THRESHOLD)
          {
            state = SHORT_PRESS;
          }
          else if (now - startKey < MEDIUM_THRESHOLD)
          {
            state = MEDIUM_PRESS;
          }
          else
          {
            state = LONG_PRESS;
          }
        }
        else
        {
          state = PRESS;
          startKey = now;
        }
        break;
    }
    Serial.print("STATE:\t ");
    Serial.print(state);
    Serial.print("\t");
    Serial.println(keys[key]);
    prevKey = key;
  }
}


void handlePress(STATE state)
{
  switch (state)
  {
    case PRESS:
      //  handle very short press.
      break;
    case SHORT_PRESS:
      //  handle short press.
      break;
    case MEDIUM_PRESS:
      //  handle medium press.
      break;
    case LONG_PRESS:
      //  handle short press.
      break;
    default:
      //  do nothing
      break;
  }
}

//  -- END OF FILE --
