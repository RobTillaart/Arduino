//    FILE: I2C_LCD_media_player_chars.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo I2C_LCD library
//     URL: https://github.com/RobTillaart/I2C_LCD


#include "I2C_LCD.h"


I2C_LCD lcd(39);

uint8_t media_player[8][8] =
{
  { 0x11, 0x13, 0x17, 0x1F, 0x1F, 0x17, 0x13, 0x11 },   //  skip backward
  { 0x01, 0x03, 0x07, 0x1F, 0x1F, 0x07, 0x03, 0x01 },   //  back
  { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },   //  stop
  { 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B },   //  pause
  { 0x10, 0x18, 0x1C, 0x1F, 0x1F, 0x1C, 0x18, 0x10 },   //  start
  { 0x11, 0x19, 0x1D, 0x1F, 0x1F, 0x1D, 0x19, 0x11 },   //  skip forward
  { 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10 },   //  free
  { 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10 }    //  free
};


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("I2C_LCD_LIB_VERSION: ");
  Serial.println(I2C_LCD_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);

  lcd.begin(20, 4);
  Serial.print("Connected: ");
  Serial.println(lcd.isConnected());

  lcd.display();
  lcd.clear();
  lcd.setCursor(0, 0);

  for (int i = 0; i < 8; i++)
  {
    lcd.createChar(i, media_player[i]);
    delay(5);
  }

  lcd.clear();
  lcd.center(0, "Media Player chars");

  lcd.setCursor(0, 2);
  lcd.print(" ");

  lcd.special(1);
  lcd.special(1);
  lcd.print(" ");

  for (int i = 0; i < 6; i++)
  {
    lcd.special(i);
    lcd.print(" ");
  }
  lcd.special(4);
  lcd.special(4);

}


void loop()
{
}


//  -- END OF FILE --
