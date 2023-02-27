//
//    FILE: ansi_clearline.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/ANSI


#include "ansi.h"

ANSI ansi(&Serial);


void setup()
{
  Serial.begin(115200);

  ansi.clearScreen();
  for (int i = 0; i < 20; i++)
  {
    ansi.println("1234567890123456789012345678901234567890");
    delay(100);
  }
  delay(1000);

  for (int i = 0; i < 8; i++)
  {
    ansi.gotoXY(4 + 2 * i, i);
    ansi.clearLine(ansi.toEnd);
    delay(100);
  }
  delay(1000);

  for (int i = 12; i < 20; i++)
  {
    ansi.gotoXY(4 + 2 * i, i);
    ansi.clearLine(ansi.toStart);
    delay(100);
  }
  delay(1000);

  for (int i = 9; i < 11; i++)
  {
    ansi.gotoXY(4 + 2 * i, i);
    ansi.clearLine(ansi.entireLine);
    delay(100);
  }
  delay(1000);
}


void loop()
{
}


//  -- END OF FILE --

