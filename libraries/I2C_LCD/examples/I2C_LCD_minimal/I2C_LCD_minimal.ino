//    FILE: I2C_LCD_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo I2C_LCD library
//     URL: https://github.com/RobTillaart/I2C_LCD


#include "I2C_LCD.h"


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
  lcd.begin(20, 4);

  //  display fixed text once
  lcd.setCursor(0, 0);
  lcd.print("millis: ");
}


void loop()
{
  lcd.setCursor(8, 0);
  lcd.print(millis());
  delay(1000);
}


//  -- END OF FILE --
