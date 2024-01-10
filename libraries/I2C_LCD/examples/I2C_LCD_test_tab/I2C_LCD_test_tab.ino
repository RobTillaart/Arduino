//    FILE: I2C_LCD_test_tab.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo I2C_LCD library
//     URL: https://github.com/RobTillaart/I2C_LCD


#include "I2C_LCD.h"


//  test 20x4 + 16x2
#define BACKLIGHT_PIN   3
#define En_pin          2
#define Rw_pin          1
#define Rs_pin          0
#define D4_pin          4
#define D5_pin          5
#define D6_pin          6
#define D7_pin          7


I2C_LCD lcd(39);


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("I2C_LCD_LIB_VERSION: ");
  Serial.println(I2C_LCD_LIB_VERSION);
  Serial.println((int)'\t');

  // lcd.config(39, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin, BACKLIGHT_PIN, POSITIVE);

  Wire.begin();
  Wire.setClock(100000);
  lcd.begin(20, 4);

  lcd.display();
  lcd.clear();
  lcd.print("TAB demo:\t");
  lcd.print(I2C_LCD_LIB_VERSION);

  for (int r = 1; r < 4; r++)
  {
    lcd.setCursor(0, r);
    for (int i = 0; i < 5; i++)
    {
      // lcd.print(lcd.getColumn());
      lcd.print(random(100));
      lcd.print('\t');
    }
  }

}


void loop()
{
}


//  -- END OF FILE --
