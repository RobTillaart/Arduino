#pragma once
//
//    FILE: ansi.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.7
// PURPOSE: Arduino library to send ANSI escape sequences
//    DATE: 2020-04-28
//     URL: https://github.com/RobTillaart/ANSI
//


#include "Arduino.h"

#define ANSI_LIB_VERSION        (F("0.1.7"))


class ANSI : public Stream
{
public:
  ANSI(Stream * stream = &Serial);

  //  Stream interface
  int  available();
  int  read();
  int  peek();
  void flush()     { return; };  //  placeholder to keep CI happy


  //  CHAR MODES
  void normal()    { print("\033[0m"); };
  void bold()      { print("\033[1m"); };
  void low()       { print("\033[2m"); };
  void underline() { print("\033[4m"); };
  void blink()     { print("\033[5m"); };
  void reverse()   { print("\033[7m"); };


  //  COLOR
  enum {
    black = 0,
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    white,
    bright, //  Add this to any of the previous 8 to get a bright color
  };

  //  foreground, background, and color accept one of the following colors:
  //  * color name from above:          ANSI::red
  //  * bright color name from above:   ANSI::red + ANSI::bright
  //  * gray color:                     ANSI::gray2color(gray)
  //  * RGB color:                      ANSI::rgb2color(r, g, b)

  //  Set foreground color
  void foreground(uint8_t fgcolor);
  //  Set background color
  void background(uint8_t bgcolor);
  //  Set foreground and background color 
  //  (for named colors, this is 25% faster than setting one then the other)
  void color(uint8_t fgcolor, uint8_t bgcolor);

  //  Convert gray to ANSI 24-level gray in 4-bit colorspace
  //  Pass in a gray level from 0 (black) to 255 (white)
  uint8_t gray2color(uint8_t gray) { return 232 + uint16_t(gray) * 24 / 256; }
  uint8_t grey2color(uint8_t grey) { return this->gray2color(grey); }
  //  Convert RGB color to ANSI color in 4-bit colorspace
  //  Pass in a RGB level from 0 (dark) to 255 (light)
  uint8_t rgb2color(uint8_t r, uint8_t g, uint8_t b);


  //  POSITIONING
  enum {
    toEnd = 0,
    toStart = 1,
    entireLine = 2,
  };

  void clearScreen();
  void clearLine(uint8_t clear = toEnd);

  void home()      { print("\033[H");  };

  void gotoXY(uint8_t x, uint8_t y);
  void cursorUp(uint8_t x);
  void cursorDown(uint8_t x);
  void cursorForward(uint8_t x);
  void cursorBack(uint8_t x);


  //  META
  //  deviceType is discussed 
  //    - https://github.com/RobTillaart/ANSI/issues/9
  //  timeout in milliseconds. 
  //  note this function blocks for timeout or less.
  //  -1 = unknown; 
  //   1 = VT52, 2 = VT100, 3 = VT220,
  int deviceType(uint32_t timeout = 100);


  //  EXPERIMENTAL SECTION
  //  use at own risk
  //  check if it works on your terminal              Tera
  /*
  void set132()          { print("\033[?3h");  };  //  +
  void set80()           { print("\033[?3l");  };  //  +
  void setSmoothScroll() { print("\033[?4h");  };  //  -
  void setJumpScroll()   { print("\033[?4l");  };  //  -
  void moveWindowDown()  { print("\033M");     };  //  +
  void moveWindowUp()    { print("\033D");     };  //  +
  //  to be used for password?
  void invisible()       { print("\033[8m");   };  //  -

  //  PRINTING
  //  use at own risk
  //  check if it works on your terminal              Tera
  void printScreen()     { print("\033[i");    };  //  +
  void printLine()       { print("\033[1i");   };  //  ?
  void startPrintLog()   { print("\033[4i");   };  //  ?
  void stopPrintLog()    { print("\033[5i");   };  //  ?

  //  Reset terminal to initial state
  void reset()           { print("\033c");     };  //  +
  */

private:
  size_t write(uint8_t c);
  size_t write(uint8_t * array, uint8_t length);
  void color4(uint8_t base, uint8_t color);
  void color4_code(uint8_t base, uint8_t color);
  void colors4(uint8_t fgcolor, uint8_t bgcolor);
  void color8(uint8_t base, uint8_t color);

  Stream *   _stream;

};


// -- END OF FILE --

