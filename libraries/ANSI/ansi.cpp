//
//    FILE: ansi.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: Arduino library to send ANSI escape sequences
//    DATE: 2020-04-28
//     URL: https://github.com/RobTillaart/ANSI
//
// 0.1.0    2020-04-28  initial version
// 0.1.1    2020-05-27  update library.json
// 0.1.2    2020-07-08  added clearLine + color support (thanks airbornemint)
// 0.1.3    2020-12-11  added arduino-ci + unit test (minimal)

#include "ansi.h"

ANSI::ANSI(Stream * stream)
{
  _stream = stream;
}

int ANSI::available()
{
	return _stream->available();
}

int ANSI::read()
{
	return _stream->read();
}

int ANSI::peek()
{
	return _stream->peek();
}

void ANSI::clearScreen()
{
  print("\033[2J");
  home();
}

void ANSI::clearLine(uint8_t clear)
{
  print("\033[");
  print(clear);
  print("K");
}
// ANSI has three different color spaces: 4-bit color, 8-bit color, and 24-bit color
// The are rendered with SGR 30-37,90-97/40-47,100-107, SGR 38;5/48;5, and SGR 38;2/48;2, respectively
// The 4-bit color space is the most widely compatible and the most compactly transmitted
enum {
  fg_normal = 30,
  bg_normal = 40,
  bright_color = 52,

  extended_color = 8,
  extended_color8 = 5,
  extended_color24 = 2,
};

void ANSI::color4_code(uint8_t base, uint8_t color) {
  if (color < 8) {
    print(base + color);
  } else {
    print(base + bright_color + color);
  }
}

void ANSI::color4(uint8_t base, uint8_t color) {
  print("\033[");
  this->color4_code(base, color);
  print("m");
}

void ANSI::colors4(uint8_t fgcolor, uint8_t bgcolor) {
  print("\033[");
  this->color4_code(fg_normal, fgcolor);
  print(";");
  this->color4_code(bg_normal, bgcolor);
  print("m");
}

void ANSI::color8(uint8_t base, uint8_t color) {
  print("\033[");
  print(base + extended_color);
  print(";");
  print(extended_color8);
  print(";");
  print(color);
  print("m");
}

void ANSI::foreground(uint8_t fgcolor)
{
  if (fgcolor < 16) {
    this->color4(fg_normal, fgcolor);
  } else {
    this->color8(fg_normal, fgcolor);
  }
}

void ANSI::background(uint8_t bgcolor)
{
  if (bgcolor < 16) {
    this->color4(bg_normal, bgcolor);
  } else {
    this->color8(bg_normal, bgcolor);
  }
}

void ANSI::color(uint8_t fgcolor, uint8_t bgcolor)
{
  if (fgcolor < 16 && bgcolor < 16) {
    this->colors4(fgcolor, bgcolor);
  } else {
    this->color8(fg_normal, fgcolor);
    this->color8(bg_normal, bgcolor);
  }
}

uint8_t ANSI::rgb2color(uint8_t r, uint8_t g, uint8_t b) {
  return 16 +
    36 * (uint16_t(r) * 6 / 256) + 
    6 * (uint16_t(g) * 6 / 256) + 
    (uint16_t(b) * 6 / 256);
}

void ANSI::gotoXY(uint8_t x, uint8_t y)
{
  print("\033[");
  print(x);
  print(";");
  print(y);
  print("H");
}

void ANSI::cursorUp(uint8_t x)
{
  print("\033[");
  print(x);
  print("A");
}

void ANSI::cursorDown(uint8_t x)
{
  print("\033[");
  print(x);
  print("B");
}

void ANSI::cursorForward(uint8_t x)
{
  print("\033[");
  print(x);
  print("C");
}

void ANSI::cursorBack(uint8_t x)
{
  print("\033[");
  print(x);
  print("D");
}

size_t ANSI::write(uint8_t c)
{
  // todo add line buffer
  _stream->write(c);
  return 1;
}
  
// -- END OF FILE --
