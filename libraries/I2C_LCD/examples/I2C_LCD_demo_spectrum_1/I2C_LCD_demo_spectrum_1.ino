//    FILE: I2C_LCD_demo_spectrum_1.ino
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

//  note the full filled block => lcd.special(255);
//  but code wise adding it gives simple logic.
uint8_t block[8][8] =
{
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F },
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F },
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F },
  { 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F },
  { 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
  { 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
  { 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
  { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
};


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("I2C_LCD_LIB_VERSION: ");
  Serial.println(I2C_LCD_LIB_VERSION);
  Serial.println();

  lcd.config(39, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin, BACKLIGHT_PIN, POSITIVE);

  delay(80);
  Wire.begin();
  Wire.setClock(100000);
  lcd.begin(20, 4);

  for (int i = 0; i < 8; i++)
  {
    lcd.createChar(i, block[i]);
  }
  lcd.display();
  lcd.clear();
  lcd.setCursor(0, 0);

  lcd.setCursor(0, 0);
  lcd.print(" SPECTRUM  ANALYZER ");
  lcd.setCursor(0, 1);
  lcd.print(" LEFT         RIGHT ");

  lcd.setCursor(0, 3);
  lcd.repeat('=', 20);
}


void loop()
{
  lcd.setCursor(1, 2);
  for (int i = 1; i < 9; i++)
  {
    int a = random(8);
    lcd.special(a);
  }
  lcd.setCursor(11, 2);
  for (int i = 1; i < 9; i++)
  {
    int a = random(8);
    lcd.special(a);
  }
  delay(200);
}


//  -- END OF FILE --
