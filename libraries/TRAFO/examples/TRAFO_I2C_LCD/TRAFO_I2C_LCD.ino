//
//    FILE: TRAFO_I2C_LCD.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/TRAFO


#include "TRAFO.h"
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

TRAFO myTrafo;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("I2C_LCD_LIB_VERSION: \t");
  Serial.println(I2C_LCD_LIB_VERSION);
  Serial.print("TRAFO_LIB_VERSION: \t");
  Serial.println(TRAFO_LIB_VERSION);
  Serial.println();

  myTrafo.begin(readADC, 1023, 5.12, 708);

  lcd.config(39, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin, BACKLIGHT_PIN, POSITIVE);

  Wire.begin();
  Wire.setClock(400000);
  lcd.begin(20, 4);

  lcd.display();
  lcd.clear();
  lcd.home();
  lcd.setCursor(0, 0);
  lcd.print("ZERO: ");
  lcd.setCursor(0, 1);
  lcd.print("FREQ: ");
  lcd.setCursor(0, 2);
  lcd.print(" RMS: ");
}


void loop()
{
  float freq = myTrafo.detectFrequency(5);
  int zero = myTrafo.getZeroPoint();
  //int adc = myTrafo.getADC();
  float rms = myTrafo.getRMS();

  Serial.print(zero);
  Serial.print("\t");
  Serial.print(freq, 2);
  Serial.print("\t");
  Serial.print(rms, 1);
  Serial.print("\t");
  Serial.println();

  lcd.setCursor(6, 0);
  lcd.print(zero);
  lcd.print("  ");
  lcd.setCursor(6, 1);
  lcd.print(freq, 2);
  lcd.print("  ");
  lcd.setCursor(6, 2);
  lcd.print(rms, 1);
  lcd.print("   ");

  delay(1000);
}


int32_t readADC()
{
  return (int32_t)analogRead(A0);
}


//  -- END OF FILE --
