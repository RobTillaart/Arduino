//    FILE: I2C_LCD_demo_80chars.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo I2C_LCD library performance test
//     URL: https://github.com/RobTillaart/I2C_LCD
//  https://forum.arduino.cc/t/80-char-array-for-4x20-lcd/1325371/18

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

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("I2C_LCD_LIB_VERSION: ");
  Serial.println(I2C_LCD_LIB_VERSION);
  Serial.println();

  lcd.config(39, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin, BACKLIGHT_PIN, POSITIVE);

  Wire.begin();
  Wire.setClock(100000);
  lcd.begin(20, 4);

  lcd.display();
  lcd.clear();
}


void loop()
{
  lcd.clear();
  delay(100);
  start = micros();
  lcd.setCursor(0, 0);
  //                   1111111111
  //         01234567890123456789
  lcd.print("ABCDEFGHIJKLMNOPQRST");

  lcd.setCursor(0, 1);
  //                   1111111111
  //         01234567890123456789
  lcd.print("UVWXYZ0123456789****");

  lcd.setCursor(0, 2);
  //                   1111111111
  //         01234567890123456789
  lcd.print("abcdefghijklmnopqrst");

  lcd.setCursor(0, 3);
  //                   1111111111
  //         01234567890123456789
  lcd.print("uvwxyz0123456789****");
  stop = micros();
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(stop - start);

  Serial.println(stop - start);
  delay(2000);
}


//  -- END OF FILE --
