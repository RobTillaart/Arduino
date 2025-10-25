//    FILE: I2C_LCD_multi.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo I2C_LCD library
//     URL: https://github.com/RobTillaart/I2C_LCD


//  TO BE TESTED

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



//  4 LCD's in a 2x2 matrix
I2C_LCD lcd0(38);
I2C_LCD lcd1(39);
I2C_LCD lcd2(40);
I2C_LCD lcd3(41);

I2C_LCD *lcd = &lcd0;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("I2C_LCD_LIB_VERSION: ");
  Serial.println(I2C_LCD_LIB_VERSION);
  Serial.println();

  //  an array could be easier
  lcd0.config(38, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin, BACKLIGHT_PIN, POSITIVE);
  lcd1.config(39, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin, BACKLIGHT_PIN, POSITIVE);
  lcd2.config(40, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin, BACKLIGHT_PIN, POSITIVE);
  lcd3.config(41, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin, BACKLIGHT_PIN, POSITIVE);

  Wire.begin();
  Wire.setClock(100000);
  lcd0.begin(20, 4);
  lcd1.begin(20, 4);
  lcd2.begin(20, 4);
  lcd3.begin(20, 4);

  superXY(25, 7);
  superPrint("hello");

}


void loop()
{
}


void superXY(int x, int y)
{
  if (x < 20 && y < 4) { lcd = &lcd0; lcd->setCursor(x,    y   ); };
  if (x < 20 && y > 3) { lcd = &lcd1; lcd->setCursor(x,    y-4 ); };
  if (x > 19 && y < 4) { lcd = &lcd2; lcd->setCursor(x-20, y   ); };
  if (x > 19 && y > 3) { lcd = &lcd3; lcd->setCursor(x-20, y-4 ); };
}


void superPrint(char * str)
{
  lcd->print(str);
}
