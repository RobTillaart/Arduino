//
//    FILE: ansi.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.2
// PURPOSE: Arduino library to send ANSI escape sequences
//    DATE: 2020-04-28
//     URL: https://github.com/RobTillaart/ANSI


#include "ansi.h"


ANSI::ANSI(Stream * stream)
{
  _stream = stream;
}


//////////////////////////////////////////////////////
//
//  STREAM INTERFACE
//
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


void ANSI::flush()
{
  return;
}


//////////////////////////////////////////////////////
//
//  CHAR MODES
//
void ANSI::normal()
{
  _stream->write("\033[0m", 4);
}

void ANSI::bold()
{
  _stream->write("\033[1m", 4);
}

void ANSI::low()
{
  _stream->write("\033[2m", 4);
}

void ANSI::underline()
{
  _stream->write("\033[4m", 4);
}

void ANSI::blink()
{
  _stream->write("\033[5m", 4);
}

void ANSI::blinkFast()
{
  _stream->write("\033[6m", 4);
}

void ANSI::reverse()
{
  _stream->write("\033[7m", 4);
}


//////////////////////////////////////////////////////
//
//  POSITION COMMANDS
//
void ANSI::clearScreen()
{
  _stream->write("\033[2J\033[H", 7);
}

void ANSI::clearLine(uint8_t clear)
{
  _stream->write("\033[", 2);
  print(clear);
  _stream->write('K');
}

void ANSI::home()
{
  _stream->write("\033[H", 3);
}

//  changed 0.2.0 see #13
void ANSI::gotoXY(uint8_t column, uint8_t row)
{
  _stream->write("\033[", 2);
  print(row);
  _stream->write(';');
  print(column);
  _stream->write('H');
}

void ANSI::cursorUp(uint8_t x)
{
  _stream->write("\033[", 2);
  print(x);
  _stream->write('A');
}

void ANSI::cursorDown(uint8_t x)
{
  _stream->write("\033[", 2);
  print(x);
  _stream->write('B');
}

void ANSI::cursorForward(uint8_t x)
{
  _stream->write("\033[", 2);
  print(x);
  _stream->write('C');
}

void ANSI::cursorBack(uint8_t x)
{
  _stream->write("\033[", 2);
  print(x);
  _stream->write('D');
}


//////////////////////////////////////////////////////
//
//  COLOR COMMANDS
//

//  ANSI has three different color spaces: 4-bit color, 8-bit color, and 24-bit color
//  These are rendered with SGR 30-37,90-97/40-47,100-107, SGR 38;5/48;5, and SGR 38;2/48;2, respectively
//  The 4-bit color space is the most widely compatible and the most compactly transmitted
enum {
  fg_normal = 30,
  bg_normal = 40,
  bright_color = 52,

  extended_color = 8,
  extended_color8 = 5,
  extended_color24 = 2,
};


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


int ANSI::deviceType(uint32_t timeout)
{
  int type = -1;        //  -1 = unknown
  print("\033[0c");

  char buffer[4];
  int len = 0;
  char c;
  uint32_t start = millis();
  while ((len < 3) && ((millis() - start) < timeout))
  {
    if (_stream->available())
    {
      c = _stream->read();
      buffer[len++] = c;
      buffer[len] = 0;
    }
  }

  if ((buffer[0] == '1') && (buffer[1] == ';'))
  {
    type = buffer[2] - '0';
  }
  return type;
}


bool ANSI::readCursorPosition(uint16_t &w, uint16_t &h, uint32_t timeout)
{
  print("\033[6n");

  char buffer[16];
  int len = 0;
  char c;
  uint32_t start = millis();
  while (millis() - start < timeout)
  {
    if (_stream->available())
    {
      c = _stream->read();
      buffer[len++] = c;
      buffer[len] = 0;
      if (c == 'R') break;
    }
  }
  //  do we have enough chars
  //  typical (8) = \e[24;80R
  //  minimal (6) = \e[1;1R
  if (len < 6) return false;
  //  last char must be R to have them all.
  if (c != 'R') return false;

  //  parse the buffer
  int number[2] = {0, 0};
  int i = 0;
  // read digits.
  for (int n = 0; n < 2; n++)
  {
    //  skip until digits
    while ((i < len) && !isdigit(buffer[i])) i++;
    // read number
    while ((i < len) && isdigit(buffer[i]))
    {
      number[n] *= 10;
      number[n] += buffer[i] - '0';
      i++;
    }
  }
  w = number[1];
  h = number[0];
  return ((w > 0) && (h > 0));
}


bool ANSI::getScreenSize(uint16_t &w, uint16_t &h, uint32_t timeout)
{
  //  gotoXY(9999,9999);
  print("\033[9999;9999H");
  bool rv = readCursorPosition(w, h, timeout);
  _width  = w;
  _height = h;
  return rv;
}


//////////////////////////////////////////////////
//
//  PROTECTED
//
size_t ANSI::write(uint8_t c)
{
  //  add line buffer? - interference with write(array, length) !?
  return _stream->write(c);
}


size_t ANSI::write(uint8_t * array, uint8_t length)
{
  return _stream->write(array, length);
}


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


//////////////////////////////////////////////////////
//
//  DERIVED
//
VT100::VT100(Stream * stream) : ANSI(stream)
{
}


//  -- END OF FILE --

