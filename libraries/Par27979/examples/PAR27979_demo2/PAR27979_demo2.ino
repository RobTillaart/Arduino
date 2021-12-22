//
//    FILE: par27979_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-06-23
//    (c) : MIT


#include "PAR27979.h"

PAR27979 display(&Serial);


void setup()
{
  Serial.begin(19200);  // max speed parallax display

  display.clearHome();

  // ON OFF TEST
  display.on();
  delay(1000);
  display.off();
  delay(1000);
  display.on();

  // BACKLIGHT TEST
  display.backlightOn();
  delay(1000);
  display.backlightOff();
  delay(1000);
  display.backlightOn();

  // PRINT
  display.gotoXY(0, 0);
  display.print(10);
  delay(100);
  display.println();
  display.print(-10);
  delay(100);
  display.println();
  display.print(20L);
  delay(100);
  display.println();
  display.print(-20L);
  delay(100);
  display.println();
  display.print(PI, 7);
  delay(100);
  display.print(F("that is"));
  display.print("all folks");
  delay(1000);

  // CUSTOM CHAR
  uint8_t ch_array[8] = { 0, 2, 4, 8, 31, 8, 4, 2 };
  display.defineCustomChar(0, ch_array);
  display.customChar(0);

  // PLAY
  display.duration(64);  // 1 second.
  display.octave(4);
  for (int n = 0; n < 12; n++) display.play(n);
  display.noSound();

  // FINISH
  display.clearHome();
  display.print("Done...");
}


void loop()
{
}


// -- END OF FILE --

