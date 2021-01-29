//
//    FILE: ansiDemo01.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2020-04-28
//     URL: https://github.com/RobTillaart/ANSI
//    (c) : MIT
//

#include "ansi.h"

ANSI ansi(&Serial);


void setup()
{
  Serial.begin(115200);

  ansi.clearScreen();
  ansi.bold();
  ansi.println("Hello world");
  ansi.blink();
  ansi.println("Hello world");
  ansi.underline();
  ansi.println("Hello world");
  ansi.low();
  ansi.println("Hello world");
  ansi.reverse();
  ansi.println("Hello world");
  ansi.normal();
  ansi.println("Hello world");
  delay(1000);

  ansi.clearScreen();
  ansi.println("Hello world");
  ansi.println("Hello world");
  ansi.println("Hello world");
  delay(1000);

  ansi.clearScreen();
  for (int i = 1; i < 25; i++)
  {
    ansi.gotoXY(i, 2 * i);
    ansi.println("Hello world");
    delay(100);
  }
  delay(1000);

  ansi.clearScreen();
  // 4 bit color test
  for (int color = 0; color < 16; ++color) {
    ansi.foreground(color);
    ansi.print("foreground");
    ansi.normal();
    ansi.background(color);
    ansi.println("background");
    ansi.normal();
  }

  delay(1000);

  ansi.clearScreen();
  for (int color = 0; color < 16; ++color) {
    ansi.color(color, (color + 1) % 16);
    ansi.println("foreground and background");
    ansi.normal();
  }

  delay(1000);

  ansi.clearScreen();
  // 8 bit color test
  ansi.foreground(ansi.rgb2color(180, 0, 158));
  ansi.print("foreground");
  ansi.normal();
  ansi.background(ansi.rgb2color(180, 0, 158));
  ansi.println("background");
  ansi.normal();

  ansi.foreground(ansi.grey2color(64));
  ansi.print("foreground");
  ansi.normal();
  ansi.background(ansi.grey2color(64));
  ansi.println("background");
  ansi.normal();

  delay(1000);
  ansi.normal();
}

void loop()
{
}

// -- END OF FILE --