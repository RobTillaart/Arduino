//
//    FILE: ansi_clock.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo clock
//     URL: https://github.com/RobTillaart/ANSI
//
//  use Tera Term to view 'different' clocks.

#include "ansi.h"

ANSI ansi(&Serial);

int hh = 0;
int mm = 0;
int ss = 0;

void setup()
{
  Serial.begin(115200);

  //  SPLASH SCREEN
  ansi.clearScreen();
  ansi.gotoXY(8, 10);
  ansi.bold();
  ansi.print("DEMO ANSI TERMINAL");
  ansi.normal();
  delay(3000);
  ansi.clearScreen();

  //  uses compile time
  sscanf(__TIME__, "%d:%d:%d", &hh, &mm, &ss);
}


void loop()
{
  update_time();
  display_time_1();
  display_time_2();
  display_time_3();
}


void update_time()
{
  static uint32_t lastTime = 0;
  uint32_t now = millis();
  if (now - lastTime >= 1000)
  {
    lastTime = now;
    ss++;
    if (ss == 60)
    {
      ss = 0;
      mm++;
    };
    if (mm == 60)
    {
      mm = 0;
      hh++;
    };
    if (hh == 24)
    {
      hh = 0;
    };
  }
}


//  displays time per second
void display_time_1()
{
  static uint32_t lastTime = 0;
  uint32_t now = millis();
  if (now - lastTime >= 1000)
  {
    lastTime = now;
    ansi.gotoXY(10, 2);
    ansi.print("TIME:         ");
    ansi.gotoXY(16, 2);
    if (hh < 10) ansi.print(0);
    ansi.print(hh);
    ansi.print(':');
    if (mm < 10) ansi.print(0);
    ansi.print(mm);
    ansi.print(':');
    if (ss < 10) ansi.print(0);
    ansi.print(ss);
  }
}


//  updates time every 5 seconds
void display_time_2()
{
  static uint32_t lastTime = 0;
  uint32_t now = millis();
  if (now - lastTime >= 1000 && (ss % 5 == 0))
  {
    lastTime = now;
    ansi.gotoXY(10, 4);
    ansi.print("TIME:         ");
    ansi.gotoXY(16, 4);
    if (hh < 10) ansi.print(0);
    ansi.print(hh);
    ansi.print(':');
    if (mm < 10) ansi.print(0);
    ansi.print(mm);
    ansi.print(':');
    if (ss < 10) ansi.print(0);
    ansi.print(ss);
  }
}


//  displays hours and minutes and a blink ".:" per second.
void display_time_3()
{
  static uint32_t lastTime = 0;
  uint32_t now = millis();
  if (now - lastTime >= 1000)
  {
    lastTime = now;
    ansi.gotoXY(10, 6);
    ansi.print("TIME:         ");
    ansi.gotoXY(16, 6);
    if (hh < 10) ansi.print(0);
    ansi.print(hh);
    if (ss & 0x01) ansi.print(':');
    else ansi.print('.');
    if (mm < 10) ansi.print(0);
    ansi.print(mm);
  }
}


//  -- END OF FILE --
