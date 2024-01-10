//    FILE: I2C_LCD_demo_alignment.ino
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
  Serial.println();

  lcd.config(39, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin, BACKLIGHT_PIN, POSITIVE);

  Wire.begin();
  Wire.setClock(100000);
  lcd.begin(20, 4);

  //  show centring
  lcd.clear();
  lcd.center(0, "1234567890");
  lcd.center(1, "123456789");
  lcd.center(2, "23456789");
  lcd.center(3, "2345678");
  delay(5000);

}


void loop()
{
  lcd.clear();
  for (int r = 0; r < 4; r++)
  {
    int x = random(20000);
    char buffer[8];
    itoa(x, buffer, 10);
    lcd.right(8, r, buffer);
  }
  for (int r = 0; r < 4; r++)
  {
    int x = random(20000);
    char buffer[8];
    itoa(x, buffer, 10);
    lcd.right(18, r, buffer);
  }
  delay(2000);
}


//  -- END OF FILE --
