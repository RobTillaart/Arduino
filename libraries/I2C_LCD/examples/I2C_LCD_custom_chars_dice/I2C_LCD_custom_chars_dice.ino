//    FILE: I2C_LCD_custom_chars_dice.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo I2C_LCD library
//     URL: https://github.com/RobTillaart/I2C_LCD


#include "I2C_LCD.h"

uint8_t dice_chars[6][8]
{
  { 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00 },  //  1
  { 0x00, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00 },  //  2
  { 0x00, 0x10, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00 },  //  3
  { 0x00, 0x11, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00 },  //  4
  { 0x00, 0x11, 0x00, 0x04, 0x00, 0x11, 0x00, 0x00 },  //  5
  { 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0x00, 0x00 }   //  6
};


I2C_LCD lcd(39);


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
  lcd.setCursor(3, 0);
  lcd.print("Dice characters");

  for (int i = 0; i < 6; i++)
  {
    lcd.createChar(i, dice_chars[i]);
    delay(5);
  }

  lcd.setCursor(4, 1);
  for (int i = 0; i < 6; i++)
  {
    lcd.special(i);
    lcd.print(" ");
  }

  lcd.setCursor(0, 3);
  lcd.print("done...");
}


void loop()
{
  for (int p = 0; p < 19; p++)
  {
    lcd.setCursor(p, 2);
    lcd.special(random(6));
    delay(250);
    lcd.setCursor(p, 2);
    lcd.print(' ');
  }
  lcd.setCursor(19, 2);
  lcd.special(random(6));
  delay(2000);
}


//  -- END OF FILE --
