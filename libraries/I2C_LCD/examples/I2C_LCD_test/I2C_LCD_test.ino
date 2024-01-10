//    FILE: I2C_LCD_test.ino
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

  // lcd.config(39, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin, BACKLIGHT_PIN, POSITIVE);

  Wire.begin();
  Wire.setClock(100000);

  lcd.begin(20, 4);
  Serial.print("Connected: ");
  Serial.println(lcd.isConnected());

  lcd.clear();


  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(1);
  delay(1000);
  lcd.setBacklight(0);
  delay(1000);
  lcd.setBacklight(1);

  char buf[24] = "1234567890";
  lcd.center(0, buf);
  lcd.center(1, "123456789");
  lcd.center(2, "23456789");
  lcd.center(3, "2345678");
  delay(4000);


  lcd.clear();
  for (int r = 0; r < 4; r++)
  {
    int x = random(20000);
    char buffer[8];
    itoa(x, buffer, 10);
    lcd.right(10, r, buffer);
    lcd.moveCursorRight(2);
    lcd.print("$");
    lcd.moveCursorLeft(10);
    lcd.print("$");
  }
  delay(4000);


  lcd.clear();
  lcd.setCursor(3, 1);
  uint32_t start = micros();
  lcd.print(__TIME__);
  uint32_t stop = micros();

  lcd.setCursor(14, 1);
  lcd.print(stop - start);
  delay(1000);

  lcd.setCursor(0, 0);
  for (char c = 'A'; c <= 'Z'; c++)
  {
    lcd.print(c);
  }
  delay(2000);
}


void loop()
{
  //  lcd.clear();
  //  lcd.setCursor(0, 0);
  //  lcd.print(millis());
  //  lcd.print(" ");
  //  lcd.print(lcd.getColumn());
  //  delay(1000);
}


//  -- END OF FILE --
