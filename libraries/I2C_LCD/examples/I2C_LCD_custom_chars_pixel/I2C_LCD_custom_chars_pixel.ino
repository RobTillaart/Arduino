//    FILE: I2C_LCD_custom_chars_pixel.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo I2C_LCD library - Single pixel walk with ASDF keys
//          continuous creation of custom chars.
//     URL: https://github.com/RobTillaart/I2C_LCD


#include "I2C_LCD.h"

uint8_t pixel_char[8]
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

int x = 0, y = 0;


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
}



void loop()
{
  if (Serial.available())
  {
    int c = Serial.read();
    if (c == 'a') x = (x + 99) % 100;
    if (c == 's') x = (x + 1) % 100;
    if (c == 'd') y = (y + 1) % 32;
    if (c == 'f') y = (y + 31) % 32;
    setXY(x, y);
  }
  //  x = random(100);
  //  y = random(32);
  //  setXY(x, y);
  //  delay(1000);
}


void setXY(int x, int y)
{

  static int a = 0;
  static int b = 0;
  static int c = 0;
  static int d = 0;

  //  clear, not optimized.
  for (int i = 0; i < 8; i++) pixel_char[i] = 0;
  lcd.setCursor(a, b);
  lcd.print(' ');

  //  calculate new coordinates of char
  a = x / 5;
  b = y / 8;
  //  calculate pixel within char
  c = x - a * 5;
  d = y - b * 8;

  pixel_char[d] = 1 << (4 - c);
  //  store
  lcd.createChar(0, pixel_char);
  //  and display.
  lcd.setCursor(a, b);
  lcd.special(0);
}


//  -- END OF FILE --
