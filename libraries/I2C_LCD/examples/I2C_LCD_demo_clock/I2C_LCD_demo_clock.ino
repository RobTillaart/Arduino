//    FILE: I2C_LCD_demo_clock.ino
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


void printTime()
{
  uint32_t now = millis() / 1000;
  uint16_t hours = now / 3600;
  now -= hours * 3600;
  uint16_t minutes = now / 60;
  uint16_t seconds = now - minutes * 60;
  if (hours < 10) lcd.print(0);
  lcd.print(hours);
  lcd.print(":");
  if (minutes < 10) lcd.print(0);
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10) lcd.print(0);
  lcd.print(seconds);
}


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

  lcd.begin(16, 2); 

  lcd.display();
  lcd.clear();
}


void loop()
{
  lcd.setCursor(4, 1);
  printTime();
  delay(1000);
}


//  -- END OF FILE --
