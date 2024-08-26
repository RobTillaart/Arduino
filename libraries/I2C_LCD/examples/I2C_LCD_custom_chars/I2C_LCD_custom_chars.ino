//    FILE: I2C_LCD_custom_chars.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo I2C_LCD library
//     URL: https://github.com/RobTillaart/I2C_LCD


#include "I2C_LCD.h"
#include "I2C_LCD_custom_chars.h"


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
  lcd.setCursor(0, 0);
  lcd.print(" custom characters");
}


void loop()
{
  lcd.createChar(0, paragraph);
  lcd.setCursor(0, 2);
  lcd.special(0);

  lcd.createChar(1, copyRight);
  lcd.setCursor(1, 2);
  lcd.special(1);

  lcd.createChar(2, lessThan);
  lcd.setCursor(2, 2);
  lcd.special(2);

  lcd.createChar(3, moreThan);
  lcd.setCursor(3, 2);
  lcd.special(3);

  lcd.createChar(4, notEqual);
  lcd.setCursor(4, 2);
  lcd.special(4);
  delay(2000);



  lcd.createChar(0, doubleUP);
  lcd.setCursor(0, 2);
  lcd.special(0);

  lcd.createChar(1, doubleDOWN);
  lcd.setCursor(1, 2);
  lcd.special(1);

  lcd.createChar(2, openUP);
  lcd.setCursor(2, 2);
  lcd.special(2);

  lcd.createChar(3, openDown);
  lcd.setCursor(3, 2);
  lcd.special(3);
  delay(2000);



  lcd.createChar(0, bracketRight);
  lcd.setCursor(0, 2);
  lcd.special(0);

  lcd.createChar(1, bracketLeft);
  lcd.setCursor(1, 2);
  lcd.special(1);

  lcd.createChar(2, singleLine);
  lcd.setCursor(2, 2);
  lcd.special(2);

  lcd.createChar(3, doubleLine);
  lcd.setCursor(3, 2);
  lcd.special(3);
  delay(2000);



  lcd.createChar(0, OnOff);
  lcd.setCursor(0, 2);
  lcd.special(0);

  lcd.createChar(1, smiley);
  lcd.setCursor(1, 2);
  lcd.special(1);

  lcd.createChar(2, heart);
  lcd.setCursor(2, 2);
  lcd.special(2);

  lcd.createChar(3, euro);
  lcd.setCursor(3, 2);
  lcd.special(3);

  lcd.createChar(4, plusminus);
  lcd.setCursor(4, 2);
  lcd.special(4);
  delay(2000);

}


//  -- END OF FILE --
