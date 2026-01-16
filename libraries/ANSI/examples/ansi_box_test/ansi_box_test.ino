//
//    FILE: ansi_box_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test for box functions
//     URL: https://github.com/RobTillaart/ANSI
//
//  open Serial port with Putty or other ANSI compatible terminal.

#include "ansi.h"

ANSI ansi(&Serial);

char names[10][10]
{
  "John", "Anne", "Chloe", "James XIV", "", "", "", "", "", ""
};


void setup()
{
  Serial.begin(115200);  //  running it on 1200 baud is fun
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ANSI_LIB_VERSION: ");
  Serial.println(ANSI_LIB_VERSION);
  Serial.println();
  delay(1000);

  ansi.clearScreen();

  //  empty box
  ansi.box(4, 4, 10, 6, "");


  //  box with names
  ansi.box(24, 4, 15, 6, "NAMES");
  for (int i = 0; i < 4; i++)
  {
    ansi.gotoXY(26, 5 + i);
    ansi.print(names[i]);
  }


  // box with codes
  ansi.box(45, 4, 12, 12, "CODES");
  for (int i = 0; i < 10; i++)
  {
    ansi.gotoXY(46, 5 + i);
    ansi.print(random(10000));
  }
  delay(3000);


  //  fill screen with boxes
  ansi.clearScreen();
  for (int x = 1; x < 60; x += 10)
  {
    for (int y = 1; y < 15; y += 6)
    {
      ansi.box(x, y, 10, 6, "");
    }
  }
  delay(5000);


  ansi.clearScreen();
  //  fill screen with overlapping boxes
  for (int x = 1; x < 70; x += 9)
  {
    for (int y = 1; y < 20; y += 5)
    {
      ansi.box(x, y, 10, 6, "");
    }
  }
  delay(5000);

  ansi.clearScreen();
  ansi.fillBox(24, 4, 10, 10, '*');
  delay(100);
  ansi.fillBox(25, 5, 8, 8, ' ');
  delay(100);
  ansi.fillBox(26, 6, 6, 6, '*');
  delay(100);
  ansi.fillBox(27, 7, 4, 4, ' ');
  ansi.fillBox(28, 8, 2, 2, '*');

  delay(3000);
  ansi.clearScreen();

  ansi.gotoXY(10, 10);
  ansi.repeat("<>", 10);

  ansi.box(30, 15, 20, 6, "SCREEN SIZE");
  //  need a printXY(x,y, "....")
  uint16_t sw = 0, sh = 0;
  ansi.getScreenSize(sw, sh);
  ansi.gotoXY(34, 17);
  ansi.print(" Width: ");
  ansi.print(sw);
  ansi.gotoXY(34, 18);
  ansi.print("Heigth: ");
  ansi.print(sh);

  delay(1000);
  ansi.gotoXY(60, 25);       //  need gotoLR() depends on the size... can it be obtained?
  ansi.print("done...");
}


void loop()
{
  uint16_t sw = 0, sh = 0;
  ansi.getScreenSize(sw, sh);
  ansi.gotoXY(42, 17);
  ansi.print(sw);
  ansi.print(" ");
  ansi.gotoXY(42, 18);
  ansi.print(sh);
  ansi.print(" ");
  delay(1000);
}


//  -- END OF FILE --
