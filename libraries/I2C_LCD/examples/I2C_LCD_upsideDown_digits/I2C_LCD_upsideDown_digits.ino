//    FILE: I2C_LCD_upsideDown_digits.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo I2C_LCD library upside digits with custom characters.
//     URL: https://github.com/RobTillaart/I2C_LCD
//

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

  lcd.createChar(0, upside_1);
  lcd.createChar(1, upside_2);
  lcd.createChar(2, upside_3);
  lcd.createChar(3, upside_4);
  lcd.createChar(4, upside_5);
  lcd.createChar(5, upside_6);
  lcd.createChar(6, upside_7);
  lcd.createChar(7, upside_9);
  lcd.setCursor(0, 1);

  lcd.print("UPSIDE: ");
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
  lcd.print("done...");
  lcd.setCursor(0, 3);
  upside("TEST: 0123456789");
}


void loop()
{
}

void upside(char * str)
{
  for (uint16_t i = 0; i < strlen(str); i++)
  {
    switch (str[i])
    {
      case '0' : lcd.write('0'); break;
      case '1' : lcd.special(0); break;
      case '2' : lcd.special(1); break;
      case '3' : lcd.special(2); break;
      case '4' : lcd.special(3); break;
      case '5' : lcd.special(4); break;
      case '6' : lcd.special(5); break;
      case '7' : lcd.special(6); break;
      case '8' : lcd.write('8'); break;
      case '9' : lcd.special(7); break;
      default:   lcd.print(str[i]);
    }
  }
}


//  -- END OF FILE --
