//    FILE: I2C_LCD_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo I2C_LCD library
//     URL: todo


#include "Arduino.h"
#include "Wire.h"

#include "I2C_LCD.h"


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

  lcd.config(39, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin, BACKLIGHT_PIN);

  Wire.begin();
  Wire.setClock(400000);
  lcd.begin(20, 4);

  lcd.display();
  delay(1000);
  lcd.noDisplay();
  delay(1000);
  lcd.display();

  lcd.clear();

  lcd.home();
  lcd.setCursor(3, 3);

  uint32_t start = micros();
  lcd.print(__TIME__);
  uint32_t stop = micros();

  lcd.setCursor(10, 0);
  lcd.print(stop - start);
}


void loop()
{
  lcd.home();
  lcd.print(millis());
  delay(1000);
}


//  -- END OF FILE --
