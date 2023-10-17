//
//    FILE: ansi.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
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
  _stream->write("\033[0m", 3);
}

void ANSI::bold()
{
  _stream->write("\033[1m", 3);
}

void ANSI::low()
{
  _stream->write("\033[2m", 3);
}

void ANSI::underline()
{
  _stream->write("\033[4m", 3);
}

void ANSI::blink()
{
  _stream->write("\033[5m", 3);
}

void ANSI::reverse()
{
  _stream->write("\033[7m", 3);
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

  uint32_t start = millis();
  int read_len = 0;
  char buffer[8];
  while ((read_len != 3) && ((millis() - start) < timeout))
  {
    delay(1);
    read_len = Serial.readBytes(buffer, 3);
    if ((buffer[0] == '1') && (buffer[1] == ';'))
    {
      type = buffer[2] - '0';
    }
    //  Serial.write(buffer, 3);
    //  Serial.println();
  }
  return type;
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

