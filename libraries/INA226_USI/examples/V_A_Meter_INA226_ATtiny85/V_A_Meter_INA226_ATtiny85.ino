//
//    FILE: V_A_Meter_INA226_ATtiny85.ino
//  AUTHOR: J.P. Simoons
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/INA226_USI
//
//  need LiquidCrystal_attiny.h

#include <avr/pgmspace.h>
#include "LiquidCrystal_attiny.h"
#include "INA226.h"

#define LCD_ADDR 0x27                  // I2C address of LCD display
#define LCD_WIDTH 8                    // Number of columns of LCD display
#define LCD_HEIGHT 2                   // Number of rows of LCD display

/* connection diagram ATtiny85:
 *         Reset PB5 1 +--V--+ 8 Vcc
 *               PB3 2 |     | 7 PB2 = I2C:SCL to LCD display & INA226
 *               PB4 3 |     | 6 PB1
 *            Ground 4 +-----+ 5 PB0 = I2C:SDA to LCD display & INA226
 *
 * Note: Shunt * MAX_CURRENT must be smaller than 81,92 mV
 */
#define INA_ADDR 0x40                  // I2C address of INA module
#define SHUNT 0.1                      // INA shunt resistor for current meter in ohms
#define MAX_CURRENT 0.5                // Max current in A to be measured

/*
 * Global data
 */
char lcd_img[LCD_HEIGHT][LCD_WIDTH+1];          /* LCD image */
float bus_voltage, current;
/*
 * define objects
 */
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_WIDTH,LCD_HEIGHT);
INA226 INA(INA_ADDR);
 /*
 * Function prototype
 */
void write_lcd(void);
/*
 * Setup
 */
void setup()
{
//  lcd.begin();                                    /* standard LCD display */
  lcd.init();                                     /* "ATtiny LCD Display": initialise LCD */
  lcd.backlight();                                /* turn on backlight if not already on */
//                           01234567
  sprintf_P(lcd_img[0],PSTR("VA meter"));
  sprintf_P(lcd_img[1],PSTR("  V1.0  "));
  write_lcd();
//  Wire.begin();                                  /* already done by lcd.begin() */
//  TinyWireM.begin();                             /* ATtiny: already done by lcd.init() */
  if (!INA.begin() )
  {
    delay(1000);
//                             012345678
    sprintf_P(lcd_img[0],PSTR("*Error! *"));
    sprintf_P(lcd_img[1],PSTR(" No INA! "));
    write_lcd();
    while (true){};                       /* could not connect to INA, give up */
//    return;                       /* could not connect to INA, give up */
  }
  INA.setMaxCurrentShunt(MAX_CURRENT, SHUNT);
  delay(5000);
  return;
}
/*
 * main loop
 */
void loop()
{
  unsigned short i_current,i_temp;

  bus_voltage = INA.getBusVoltage();
  current = INA.getCurrent_mA();
/*
 * Arduino sprintf does not support floating point printing.
 * convert current into integer for printing.
 * split voltage into volts and milli volts for printing
 *    01234567
 *    xx.xx  V
 *      xxx mA
 *
 *    xx.xx  V
 *    x.xxx  A
 */
  i_current = current + 0.5;          // convert to integer for printing
  bus_voltage *= 100.0;               //units of 100 mV
  i_temp = bus_voltage + 0.5;         // convert to integer for printing
  sprintf (lcd_img[0],"%4d   V",i_temp);
  lcd_img[0][4] = lcd_img[0][3];         // make place for decimal dot
  lcd_img[0][3] = lcd_img[0][2];         // make place for decimal dot
   lcd_img[0][2] = '.';
  if (lcd_img[0][1] == ' ') lcd_img[0][1] = '0';               // .00 --> 0.00
  if (lcd_img[0][3] == ' ') lcd_img[0][3] = '0';               // 0. 0 --> 0.00
  sprintf (lcd_img[1]," %4d mA",i_current);
  if (i_current >= 1000)                                      // xxxx mA --> x.xxx A
  {
    lcd_img[1][6] = ' ';                                      // mA --> A
    lcd_img[1][0] = lcd_img[1][1];        // make place for decimal dot
    lcd_img[1][1] = '.';
  }
  write_lcd();
  delay(100);                                    // not more than 10 updates / sec for display
  return;
}
/*
 * write LCD image to LCD
 * The special version of lcd.print() for I2C on an ATTiny differs in behaviour
 * It prints only the first character of the string
 * Therefore the loop in this routine looks weird.
 */
void write_lcd()
{
  unsigned char i,j;
  for (i=0;i<LCD_HEIGHT;i++)
  {
    lcd_img[i][LCD_WIDTH] = '\0';                     /* At Tiny I2C LCD Display - terminate string, not required */
    lcd.setCursor(0,i);                               /* At Tiny I2C LCD Display - set cursor to begin of right line */
    for (j=0;j<LCD_WIDTH;j++)
    {
//      if (lcd_img[i][j] < ' ') lcd_img[i][j] = ' ';   /* overwrite \0 from sprintf() with space */
      lcd.print(&lcd_img[i][j]);                      /* AtTiny print() prints only one character */
    }
//    lcd_img[i][LCD_WIDTH] = '\0';                     /* Normal (I2C) LCD display - terminate string */
//    lcd.setCursor(0,i);                               /* Normal (I2C) LCD display - set cursor to begin of right line */
//    lcd.print(lcd_img[i]);                            /* Normal (I2C) LCD display - display line */
  }
  return;
}
