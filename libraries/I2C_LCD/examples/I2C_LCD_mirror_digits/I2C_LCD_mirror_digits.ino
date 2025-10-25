//    FILE: I2C_LCD_mirror_digits.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo I2C_LCD library mirror digits with custom characters.
//     URL: https://github.com/RobTillaart/I2C_LCD
//
//  Needs right to left writing modus.

#include "I2C_LCD.h"
#include "I2C_LCD_custom_chars.h"


I2C_LCD lcd(39);


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
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
  lcd.print("NORMAL: 0123456789");

  lcd.createChar(0, mirror_1);
  lcd.createChar(1, mirror_2);
  lcd.createChar(2, mirror_3);
  lcd.createChar(3, mirror_4);
  lcd.createChar(4, mirror_5);
  lcd.createChar(5, mirror_6);
  lcd.createChar(6, mirror_7);
  lcd.createChar(7, mirror_9);
  lcd.setCursor(0, 1);

  lcd.print("MIRROR: ");
  lcd.print(0);
  lcd.special(0);
  lcd.special(1);
  lcd.special(2);
  lcd.special(3);
  lcd.special(4);
  lcd.special(5);
  lcd.special(6);
  lcd.print(8);
  lcd.special(7);

  lcd.setCursor(0, 2);
  lcd.print("Needs right to left\nmode");
}


void loop()
{
}


//  -- END OF FILE --
