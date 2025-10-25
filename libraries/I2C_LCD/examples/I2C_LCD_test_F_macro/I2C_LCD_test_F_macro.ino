//    FILE: I2C_LCD_test_F_macro.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo I2C_LCD library, printing with  F macro
//     URL: https://github.com/RobTillaart/I2C_LCD
//

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

//
//  F MACRO
//
#define FILE_MENU_HEAD     (F("File"))
#define FILE_MENU_NEW      (F("(N)ew"))
#define FILE_MENU_OPEN     (F("(O)pen"))
#define FILE_MENU_SAVE     (F("(S)ave"))

#define ABORT_RETRY        (F("(A)bort (R)etry"))

//
//  PROGMEM
//
PROGMEM const uint8_t primes[] = { 3, 5, 7, 11};
PROGMEM const uint16_t codes[] = { 1234, 65432, 0, 6147};
PROGMEM const uint32_t longs[] = { 12341234, 654321254, 0, 6147};
PROGMEM const float floats[] = { 12.34, 654.32, 0, 61.47};

//  FAILS, TO INVESTIGATE HOW
PROGMEM const char progmemstr[] = "Hello from progmem";
char buffer[20];



void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("I2C_LCD_LIB_VERSION: ");
  Serial.println(I2C_LCD_LIB_VERSION);
  Serial.println();

  // lcd.config(39, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin, BACKLIGHT_PIN, POSITIVE);

  Wire.begin();
  Wire.setClock(100000);

  lcd.begin(20, 4);
  Serial.print("Connected: ");
  Serial.println(lcd.isConnected());

  //
  //  F MACRO
  //
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(FILE_MENU_HEAD);
  lcd.setCursor(0, 1);
  lcd.print(FILE_MENU_NEW);
  lcd.setCursor(0, 2);
  lcd.print(FILE_MENU_OPEN);
  lcd.setCursor(0, 3);
  lcd.print(FILE_MENU_SAVE);
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(ABORT_RETRY);
  delay(1000);

  //
  //  PROGMEM
  //
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" uint8_t: ");
  lcd.print(pgm_read_byte_near(&primes[3]));
  delay(1000);

  lcd.setCursor(0, 1);
  lcd.print("uint16_t: ");
  lcd.print(pgm_read_word_near(&codes[3]));
  delay(1000);

  lcd.setCursor(0, 2);
  lcd.print("uint32_t: ");
  lcd.print(pgm_read_dword_near(&longs[1]));
  delay(1000);

  lcd.setCursor(0, 3);
  lcd.print("   float: ");
  lcd.print(pgm_read_float_near(&floats[1]), 4);
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print((const __FlashStringHelper*)progmemstr);
  delay(1000);
  // FAILS
  //  lcd.setCursor(0, 1);
  //  strcpy_P(buffer, (char *) pgm_read_ptr(hello));
  //  lcd.print(buffer);
  //  delay(2000);

  lcd.setCursor(0, 1);
  lcd.print("hello world");
  delay(1000);
  lcd.setCursor(6, 1);
  lcd.clearEOL();
  lcd.print("mars");  //  column is out of range!!
  delay(1000);
  lcd.setCursor(6, 1);
  lcd.print("moon");
}


void loop()
{

}


//  -- END OF FILE --
