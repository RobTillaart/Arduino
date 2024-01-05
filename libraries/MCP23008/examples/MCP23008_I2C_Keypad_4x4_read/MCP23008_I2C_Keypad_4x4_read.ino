//
//    FILE: MCP23008_I2C_Keypad_4x4_read.ino
//  AUTHOR: François Longchamp
//    DATE: 2022-09-27
// PURPOSE: Keypad MCP23008 library
//     URL: https://github.com/RobTillaart/MCP23008
//
// Tested with Seeed Studio XIAO RP2040
// Keypad used https://fr.aliexpress.com/item/1005003176287473.html


#include "MCP23008.h"


MCP23008 MCP(0x20);


const byte ROWS_OF_KEYPAD = 4;  //  four rows
const byte COLS_OF_KEYPAD = 4;  //  four columns

byte keys_of_keypad[ROWS_OF_KEYPAD][COLS_OF_KEYPAD] = {
  {1, 2, 3, 4},
  {5, 6, 7, 8},
  {9, 10,11,12},
  {13,14,15,16}
};


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MCP23008_LIB_VERSION: ");
  Serial.println(MCP23008_LIB_VERSION);
  Serial.println();
  delay(100);

  Wire.begin();
  MCP.begin();
}


void loop()
{
  bool val;

  //  rows pinMode (0 or false = pressed)
  MCP.pinMode8(0x0f);
  for (int pin = 0; pin < 4; pin++)
  {

    val = MCP.read1(pin);
    Serial.print(val);
    Serial.print(' ');
  }

  //  columns pinMode (0 or false = pressed)
  MCP.pinMode8(0xf0);
  for (int pin = 4; pin < 8; pin++)
  {

    val = MCP.read1(pin);
    Serial.print(val);
    Serial.print(' ');
  }

  //  digital pressed from referer keys_of_keypad
  MCP.pinMode8(0x0f);
  for (int r = 0; r < ROWS_OF_KEYPAD; r++)
  {

    if( MCP.read1(r) == false )  //  false = pressed
    {

      MCP.pinMode8(0xf0);
      for (int c = ROWS_OF_KEYPAD; c < ROWS_OF_KEYPAD+COLS_OF_KEYPAD; c++)
      {

        if( MCP.read1(c) == false )  //  false = pressed
        {

          Serial.print(keys_of_keypad[r][c-4]);
        }
      }

      MCP.pinMode8(0x0f);
    }
  }

  Serial.println("");
  delay(500);
}


//  -- END OF FILE -- 

