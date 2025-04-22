//
//    FILE: ansi_cursorHide.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/ANSI
//
//  should altenatingly show/hide the cursor for 5 seconds.

#include "ansi.h"

ANSI ansi(&Serial);

bool visible = true;

void setup()
{
  Serial.begin(115200);

  ansi.clearScreen();
  ansi.cursorShow();
  ansi.gotoXY(1, 10);
  ansi.print("Hello World");
}


void loop()
{
  visible = !visible;
  if (visible) ansi.cursorShow();
  else ansi.cursorHide();
  delay(5000);
}


//  -- END OF FILE --
