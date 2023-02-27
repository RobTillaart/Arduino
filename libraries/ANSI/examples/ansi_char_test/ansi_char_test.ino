//
//    FILE: ansi_char_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: brute force char test
//     URL: https://github.com/RobTillaart/ANSI


#include "ansi.h"

ANSI ansi(&Serial);


void setup()
{
  Serial.begin(115200);

  ansi.clearScreen();

  for (int i = 0; i < 255; i++)
  {
    ansi.print((char)i);
    //    if (isprint(i)) ansi.print((char)i);
    //    else ansi.print('.');
    if (i % 16 == 0) ansi.println();
  }

  ansi.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
