//
//    FILE: ansi_gotoXY.ino
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

  // SPLASH SCREEN
  ansi.clearScreen();
  ansi.gotoXY(1, 10);
  ansi.print("x = 1, y = 10");
  delay(2000);
  ansi.gotoXY(10, 1);
  ansi.print("x = 10, y = 1");
  delay(2000);
  ansi.gotoXY(5, 20);
  ansi.print("x = 5, y = 20");
  delay(2000);

  ansi.cursorForward(5);
  ansi.cursorUp(5);
  ansi.print("*");
  ansi.cursorForward(5);
  ansi.print("*");
  ansi.cursorDown(5);
  ansi.cursorBack(1);
  ansi.print("*");
  ansi.cursorBack(7);
  ansi.print("*");
}


void loop()
{
}


//  -- END OF FILE --
