//
//    FILE: ansiDemo02.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/ANSI


#include "ansi.h"

ANSI ansi(&Serial);

int t;
double d;


void setup()
{
  Serial.begin(115200);

  //  SPLASH SCREEN
  ansi.clearScreen();
  ansi.gotoXY(10, 8);
  ansi.bold();
  ansi.print("DEMO ANSI TERMINAL");
  ansi.normal();
  delay(5000);
  ansi.clearScreen();
}


void loop()
{
  //  DISPLAY TEMPERATURE (dummy)
  ansi.gotoXY(10, 6);
  ansi.print("TEMP:       ");
  ansi.gotoXY(16, 6);
  t = random(100);
  if (t > 70) ansi.foreground(ansi.red);
  ansi.print(t);
  ansi.foreground(ansi.white);

  //  DISPLAY HUMIDITY (dummy)
  ansi.gotoXY(10, 7);
  ansi.print(" HUM:       ");
  ansi.gotoXY(16, 7);
  t = random(100);
  if (t > 50) ansi.foreground(ansi.yellow);
  ansi.print(t);
  ansi.foreground(ansi.white);

  //  DISPLAY UV (dummy)
  ansi.gotoXY(10, 8);
  ansi.print("  UV:       ");
  ansi.gotoXY(16, 8);
  d = random(10000) * 0.01;
  if (d > 30) ansi.foreground(ansi.green);
  if (d > 50) ansi.foreground(ansi.yellow);
  if (d > 70) ansi.foreground(ansi.red);
  ansi.print(d, 2);
  ansi.foreground(ansi.white);

  //  DISPLAY bar graph (dummy)
  ansi.gotoXY(10, 10);
  ansi.print(" BAR:");
  ansi.gotoXY(16, 10);
  int x = random(10);
  for (int i = 0; i < 10; i++) ansi.print(i <= x ? ">" : " ");

  //  DISPLAY password (dummy)
  ansi.gotoXY(10, 12);
  ansi.print("PASS:");
  char buffer[20];
  for (int i = 0; i < 16; i++)
  {
    int x = random(62);
    if (x < 26) buffer[i] = 'A' + random(26);
    if (26 <= x && x < 52) buffer[i] = 'a' + random(26);
    if (52 <= x) buffer[i] = '0' + random(10);
  }
  buffer[16] = 0;
  ansi.gotoXY(16, 12);
  ansi.print(buffer);

  //  DISPLAY TIME (dummy)
  ansi.gotoXY(10, 2);
  ansi.print("TIME:         ");
  ansi.gotoXY(16, 2);
  ansi.print(millis()/1000);

  delay(1000);
}


//  -- END OF FILE --

