#pragma once
//
//    FILE: ansi.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.2
// PURPOSE: Arduino library to send ANSI escape sequences
//    DATE: 2020-04-28
//     URL: https://github.com/RobTillaart/ANSI


#include "Arduino.h"

#define ANSI_LIB_VERSION        (F("0.3.2"))


class ANSI : public Stream
{
public:
  ANSI(Stream * stream = &Serial);

  //  Stream interface
  int  available();
  int  read();
  int  peek();
  void flush();  //  placeholder to keep CI happy


  //  CHAR MODES
  void normal();
  void bold();
  void low();
  void underline();
  void blink();
  void blinkFast();
  void reverse();


  //  POSITIONING
  enum {
    toEnd = 0,
    toStart = 1,
    entireLine = 2,
  };

  void clearScreen();
  void clearLine(uint8_t clear = toEnd);
  void home();

  //   gotoXY() changed in 0.2.0 See #13
  void gotoXY(uint8_t column, uint8_t row);
  void cursorUp(uint8_t x);
  void cursorDown(uint8_t x);
  void cursorForward(uint8_t x);
  void cursorBack(uint8_t x);


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

  //  Convert gray to ANSI 24-level gray in 4-bit color space
  //  Pass in a gray level from 0 (black) to 255 (white)
  uint8_t gray2color(uint8_t gray) { return 232 + uint16_t(gray) * 24 / 256; }
  uint8_t grey2color(uint8_t grey) { return this->gray2color(grey); }

  //  Convert RGB color to ANSI color in 4-bit color space
  //  Pass in a RGB level from 0 (dark) to 255 (light)
  uint8_t rgb2color(uint8_t r, uint8_t g, uint8_t b);


  ///////////////////////////////////////////////////////
  //
  //  EXPERIMENTAL SECTION
  //
  //  use at own risk
  //  check if it works on your terminal


  //  TERMINAL TYPE
  //  - https://github.com/RobTillaart/ANSI/issues/9
  //  timeout in milliseconds.
  //  note this function blocks for timeout or less.
  enum {
    UNKNOWN = -1,
    //  known types
    VT52  = 1,
    VT100 = 2,
    VT220 = 3,
    //  add others if needed.
  };
  int deviceType(uint32_t timeout = 100);


  //  SCREENSIZE
  //  - https://github.com/RobTillaart/ANSI/pull/16
  bool readCursorPosition(uint16_t &w, uint16_t &h, uint32_t timeout = 100);
  bool getScreenSize(uint16_t &w, uint16_t &h, uint32_t timeout = 100);
  //  to be used after successful call of getScreenSize();
  inline uint16_t screenWidth() { return _width; };
  inline uint16_t screenHeight() { return _height; };


  //  COLUMNS
  //  check if it works on your terminal              TERATERM
  void set132columns()   { print("\033[?3h");  };  //  +
  void set80columns()    { print("\033[?3l");  };  //  +


  //  MOVE WINDOW
  //  check if it works on your terminal              TERATERM
  void moveWindowDown()  { print("\033M");     };  //  +
  void moveWindowUp()    { print("\033D");     };  //  +


  //  PRINTING
  //  check if it works on your terminal              TERATERM
  void printScreen()     { print("\033[i");    };  //  +
  void setPrintingMode(bool on)                    //  +
       { print( on ? "\e[5i" : "\e[4i"); }


  //  RESET terminal to initial state
  void reset()           { print("\033c");     };  //  +


  //  NOT working on TERATERM (or need more testing)
  //  use at own risk
  //  check if it works on your terminal              TERATERM
  void setSmoothScroll() { print("\033[?4h");  };  //  -
  void setJumpScroll()   { print("\033[?4l");  };  //  -
  void printLine()       { print("\033[1i");   };  //  -

  //  to be used for password?
  void invisible()       { print("\033[8m");   };  //  -
  void strikeThrough()   { print("\033[9m");   };  //  -  (mobaXterm works)


  //  RGB_COLOR
  void setRGBforeground(uint8_t r, uint8_t g, uint8_t b)  //  -
  {
    print("\033[38;2;");
    write(r);
    write(';');
    write(g);
    write(';');
    write(b);
    print("m");
  };

  void setRGBbackground(uint8_t r, uint8_t g, uint8_t b)  //  -
  {
    print("\033[48;2;");
    write(r);
    write(';');
    write(g);
    write(';');
    write(b);
    print("m");
  };


protected:
  size_t write(uint8_t c);
  size_t write(uint8_t * array, uint8_t length);

  void color4(uint8_t base, uint8_t color);
  void color4_code(uint8_t base, uint8_t color);
  void colors4(uint8_t fgcolor, uint8_t bgcolor);
  void color8(uint8_t base, uint8_t color);

  Stream * _stream;

  //  screen size parameters
  uint16_t _width = 0;
  uint16_t _height = 0;
};


//////////////////////////////////////////////////////
//
//  DERIVED
//
class VT100 : public ANSI
{
public:
  VT100(Stream * stream = &Serial);
};


//  -- END OF FILE --

