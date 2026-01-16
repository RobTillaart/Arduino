//
//    FILE: ansi_cursorHide.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/ANSI
//
//  should alternately show/hide the cursor for 5 seconds.

#include "ansi.h"

ANSI ansi(&Serial);

bool visible = true;

void setup()
{
  Serial.begin(115200);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ANSI_LIB_VERSION: ");
  Serial.println(ANSI_LIB_VERSION);
  Serial.println();
  delay(1000);

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
