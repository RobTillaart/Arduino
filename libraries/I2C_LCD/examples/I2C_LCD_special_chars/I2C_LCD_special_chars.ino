//    FILE: I2C_LCD_special_chars.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo I2C_LCD library
//     URL: https://github.com/RobTillaart/I2C_LCD


#include "I2C_LCD.h"
#include "I2C_LCD_special_chars.h"


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
  lcd.print(" Special characters ");

  lcd.setCursor(0, 1);
  lcd.print(LCD_ALPHA);
  lcd.print(LCD_BETA);
  lcd.print(LCD_EPSILON);
  lcd.print(LCD_MU);
  lcd.print(LCD_SIGMA);
  lcd.print(LCD_RHO);
  lcd.print(LCD_SQROOT);

  lcd.print(LCD_THETA);
  lcd.print(LCD_INFINITY);
  lcd.print(LCD_OHM);
  lcd.print(LCD_SUM);
  lcd.print(LCD_PI);
  lcd.print(LCD_XAVG);
  lcd.print(LCD_DEGREE);
  lcd.print(LCD_DIVIDE);


  lcd.setCursor(0, 3);
  lcd.print("done...");
}


void loop()
{
}


//  -- END OF FILE --
