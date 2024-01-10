//    FILE: I2C_LCD_weather_forcast.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo I2C_LCD library
//     URL: https://github.com/RobTillaart/I2C_LCD

//  TODO: add your favo weather prediction code


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

char windDirection[8][3] =
{
  " N", "NE", " E", "SE", " S", "SW", " W", "NW"
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

  Wire.begin();
  Wire.setClock(100000);
  lcd.begin(20, 4);

  lcd.setCursor(0, 0);
  lcd.print(" DAY: We Th Fr Sa So");

  //  display temperature
  lcd.setCursor(0, 1);
  lcd.print("TEMP: ");
  for (int i = 0; i < 5; i++)
  {
    lcd.print(20 + random(10));
    lcd.print(" ");
  }

  //  alternative
  //  lcd.setCursor(0, 1);
  //  lcd.print("HUMI: ");
  //  for (int i = 0; i < 5; i++)
  //  {
  //    lcd.print(50 + random(10));
  //    lcd.print(" ");
  //  }


  lcd.setCursor(0, 2);
  lcd.print("WIND: ");
  for (int i = 0; i < 5; i++)
  {
    lcd.print(" ");
    lcd.print(random(4));
    lcd.print(" ");
  }

  lcd.setCursor(0, 3);
  lcd.print("FROM: ");
  for (int i = 0; i < 5; i++)
  {
    lcd.print(windDirection[random(8)]);
    lcd.print(" ");
  }
}


void loop()
{
}


//  -- END OF FILE --
