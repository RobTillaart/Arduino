//    FILE: I2C_LCD_demo_special_intensity.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo I2C_LCD library
//     URL: https://github.com/RobTillaart/I2C_LCD
//
//  This is a spectrum that has 10 gradations of intensity per position
//  0    = empty
//  1..8 = partial
//  9    = full

#include "I2C_LCD.h"
#include "I2C_LCD_spectrum_chars.h"


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
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("I2C_LCD_LIB_VERSION: ");
  Serial.println(I2C_LCD_LIB_VERSION);
  Serial.println();

  lcd.config(39, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin, BACKLIGHT_PIN, POSITIVE);

  Wire.begin();
  Wire.setClock(100000);

  Serial.print("CONNECT: ");
  Serial.println(lcd.isConnected());
  lcd.begin(20, 4);

  lcd.display();
  lcd.clear();
  lcd.setCursor(0, 0);

  for (int i = 0; i < 8; i++)
  {
    lcd.createChar(i, intensity[i]);
  }
  delay(10);
  lcd.clear();
  for (int i = 0; i < 8; i++)
  {
    lcd.special(i);
  }
  lcd.clear();
  delay(2000);

  uint32_t start = millis();
  for (int i = 0; i <= 144; i += 1)
  {
    spectrumRow(1, i);
    // delay(100);  //  uncomment to see it happen.
  }
  delay(100);
  for (int i = 0; i <= 144; i += 1)
  {
    spectrumRow(1, 144 - i);
    // delay(100);
  }
  uint32_t stop = millis();
  Serial.println(stop - start);
  lcd.setCursor(10, 1);
  lcd.print(stop - start);
  delay(100);

  start = millis();
  for (int i = 0; i <= 144; i += 1)
  {
    spectrumRow2(2, i);
    //  delay(100);
  }
  delay(100);
  for (int i = 0; i <= 144; i += 1)
  {
    spectrumRow2(2, 144 - i);
    //  delay(100);
  }
  stop = millis();
  Serial.println(stop - start);
  lcd.setCursor(10, 2);
  lcd.print(stop - start);
}


void loop()
{
}


//  this is not the most efficient algorithm as all of the
//  whole row is written over and over.
//  smallest footprint.
void spectrumRow(uint8_t row, int value)
{
  value = constrain(value, 0, 144);
  lcd.setCursor(0, row);
  lcd.print(value);
  lcd.print(' ');
  lcd.setCursor(4, row);
  for (uint8_t col = 4; col < 20; col++)
  {
    if (value <= 0)      lcd.print(' ');   //  replace with _
    else if (value >= 9) lcd.special(255);
    else                 lcd.special(value - 1);
    value -= 9;
  }
}


//  up to 5 times faster
//  only (re)draws the delta.
void spectrumRow2(uint8_t row, int value)
{
  static uint8_t last[4] = { 255, 255, 255, 255 };
  uint8_t start = 0;
  uint8_t end = 16;

  value = constrain(value, 0, 144);
  if (last[row] != value)
  {
    lcd.setCursor(0, row);
    lcd.print(value);
    lcd.print(' ');

    if (last[row] == 255)  //  first call.
    {
      start = 0;
      end = 16;
    }
    else
    {
      start = min(last[row] / 9, value / 9);
      end = max(last[row] / 9, value / 9) + 1;
    }
    lcd.setCursor(start + 4, row);
    last[row] = value;
    value -= (start * 9);

    for (uint8_t col = start + 4; col < end + 4; col++)
    {
      if (value <= 0)      lcd.print(' ');     //  replace with _
      else if (value >= 9) lcd.special(255);
      else                 lcd.special(value - 1);
      value -= 9;
    }
  }

}


//  -- END OF FILE --
