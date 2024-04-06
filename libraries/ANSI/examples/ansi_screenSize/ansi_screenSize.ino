//
//    FILE: ansi_screenSize.ino
//  AUTHOR: Hans Schou
// PURPOSE: demo of screen size detection
//     URL: https://github.com/RobTillaart/ANSI
//
//  These terminal emulators can report screen size:
//  * Linux, minicom
//  * Windows, PuTTY
//  * Windows, TeraTerm
//  * Windows, MobaXterm
//
//  UTF-8: To draw boxes with other than ASCII characters
//  an extra font has to be added.

#include "ansi.h"

/*
   Example output:
   +---------------------
   |
   |  Screen size: 80x24
   |
*/

ANSI ansi(&Serial);
uint16_t w, h;

void setup() {
  Serial.begin(115200);

  ansi.print(" ");  //  some bug, first character written is missing

  if (!ansi.getScreenSize(w, h, 100)) {
    ansi.println(F("\n\n### ANSI escape codes not detected ###\n"
                   "\nThis demo requires a terminal (emulator) with ANSI escape code capabilities."
                   "\nThe terminal you are using can only do TTY."
                   "\nOn Linux 'minicom' can be used. On Windows try Putty or MobaXterm."
                   "\nExample:"
                   "\n   minicom --color=on --baudrate=115200 -D /dev/ttyACM0"
                   "\n\nUTF-8 is also required. Your should see at least one emoji here?: 🐛 🖥 ☎ ❤ ❣ ✂ ✈"
                   "\n"
                   "\nSystem halted."));
    while (1) {}
  }
  ansi.clearScreen();
  ansi.gotoXY(6, 3);
  ansi.print("Screen size: ");
  ansi.print(ansi.screenWidth());
  ansi.print("x");
  ansi.println(ansi.screenHeight());
  ansi.gotoXY(6, 4);
  ansi.print("\nUTF-8 test. Your should see at least one emoji here?: 🐛 🖥 ☎ ❤ ❣ ✂ ✈");
  delay(1000);

  //  Draw border
  ansi.color(ansi.yellow, ansi.blue);
  for (uint16_t y = 1; y <= ansi.screenHeight(); y++) {
    ansi.gotoXY(1, y);
    if (1 == y || ansi.screenHeight() == y) {
      ansi.print("+");
      for (uint16_t x = 1; x < ansi.screenWidth() - 1; x++)
        ansi.print("-");
      ansi.print("+");
    } else {
      ansi.print("|");
      ansi.cursorForward(ansi.screenWidth() - 2);
      ansi.print("|");
    }
  }
  delay(3000);
}

void loop() {
}


//  -- END OF FILE --
