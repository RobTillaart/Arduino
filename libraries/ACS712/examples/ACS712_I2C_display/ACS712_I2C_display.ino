//
//    FILE: ACS712_20_AC.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo AC measurement with point to point
//     URL: https://github.com/RobTillaart/ACS712


///////////////////////////////////////////////////////////////////
//
//  DISPLAY
//
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define BACKLIGHT_PIN   3
#define En_pin          2
#define Rw_pin          1
#define Rs_pin          0
#define D4_pin          4
#define D5_pin          5
#define D6_pin          6
#define D7_pin          7

#define BL_OFF          0
#define BL_ON           1

#define DISPLAY_ADDR    0x3F    //  check

LiquidCrystal_I2C  lcd(DISPLAY_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);
uint32_t lastDisplay = 0;



#include "ACS712.h"


//  Arduino UNO has 5.0 volt with a max ADC value of 1023 steps
//  ACS712 5A  uses 185 mV per A
//  ACS712 20A uses 100 mV per A
//  ACS712 30A uses  66 mV per A


ACS712  ACS(A0, 5.0, 1023, 185);
//  ESP 32 example (might requires resistors to step down the logic voltage)
//  ACS712  ACS(25, 3.3, 4095, 185);


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("ACS712_LIB_VERSION: ");
  Serial.println(ACS712_LIB_VERSION);

  Wire.begin();

  lcd.begin(16, 2);
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(BL_ON);

  lcd.clear();

  ACS.autoMidPoint();
}


void loop()
{
  lcd.clear();

  float f1 = ACS.mA_AC();
  float f2 = ACS.mA_AC_sampling();

  lcd.setCursor(0, 0);
  lcd.print("mA: ");
  lcd.print(f1, 1);

  lcd.setCursor(10, 0);
  lcd.print(f2, 1);

  lcd.setCursor(0, 1);
  lcd.print("FF: ");
  lcd.print(f1 / f2);
  delay(1000);
}


//  -- END OF FILE --
