//
//    FILE: MATRIX7219.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2023-07-28
// PURPOSE: Arduino Library for 8x8 LED MATRIX MAX7219
//     URL: https://github.com/RobTillaart/MATRIX7219


#include "MATRIX7219.h"

#define MATRIX7219_DECODE_MODE     0x09
#define MATRIX7219_BRIGHTNESS      0x0A
#define MATRIX7219_SCAN_LIMIT      0x0B
#define MATRIX7219_SHUT_DOWN       0x0C
#define MATRIX7219_DISPLAY_TEST    0x0F


MATRIX7219::MATRIX7219(uint8_t dataPin, uint8_t selectPin, uint8_t clockPin, uint8_t matrices)
{
  _dataPin   = dataPin;
  _selectPin = selectPin;
  _clockPin  = clockPin;
  _matrices  = matrices;

   pinMode(_dataPin,  OUTPUT);
   pinMode(_selectPin,OUTPUT);
   pinMode(_clockPin, OUTPUT);

   digitalWrite(_dataPin,  HIGH);
   digitalWrite(_selectPin,HIGH);
   digitalWrite(_clockPin, HIGH);
}


uint8_t MATRIX7219::getMatrixCount()
{
  return _matrices;
}


void MATRIX7219::begin()
{
  for (int m = 0; m < _matrices; m++)
  {
    digitalWrite(_selectPin, LOW);
    _write(MATRIX7219_SCAN_LIMIT);
    _write(0x07);                       //  use bits 0..7
    digitalWrite(_selectPin, HIGH);
  }
  for (int m = 0; m < _matrices; m++)
  {
    digitalWrite(_selectPin, LOW);
    _write(MATRIX7219_DECODE_MODE);
    _write(0x00);                       //  No decode for digits 7–0
    digitalWrite(_selectPin, HIGH);
  }
  for (int m = 0; m < _matrices; m++)
  {
    digitalWrite(_selectPin, LOW);
    _write(MATRIX7219_SHUT_DOWN);
    _write(0x01);                       //  display on
    digitalWrite(_selectPin, HIGH);
  }
  for (int m = 0; m < _matrices; m++)
  {
    digitalWrite(_selectPin, LOW);
    _write(MATRIX7219_DISPLAY_TEST);
    _write(0x00);                       //  normal mode
    digitalWrite(_selectPin, HIGH);
  }
}


void MATRIX7219::setBrightness(uint8_t bright)
{
  if (bright > 15) bright = 15;

  digitalWrite(_selectPin, LOW);
  for (int m = 0; m < _matrices; m++)
  {
    _write(MATRIX7219_BRIGHTNESS);
    _write(bright);
  }
  digitalWrite(_selectPin, HIGH);
}


void MATRIX7219::displayOff()
{
  digitalWrite(_selectPin, LOW);
  for (int m = 0; m < _matrices; m++)
  {
    _write(MATRIX7219_SHUT_DOWN);
    _write(0x00);
  }
  digitalWrite(_selectPin, HIGH);
}


void MATRIX7219::displayOn()
{
  digitalWrite(_selectPin, LOW);
  for (int m = 0; m < _matrices; m++)
  {
    _write(MATRIX7219_SHUT_DOWN);
    _write(0x01);
  }
  digitalWrite(_selectPin, HIGH);
}


void MATRIX7219::displayTest(bool on)
{
  digitalWrite(_selectPin, LOW);
  for (int m = 0; m < _matrices; m++)
  {
    _write(MATRIX7219_DISPLAY_TEST);
    if (on) _write(0x01);
    else _write(0x00);
  }
  digitalWrite(_selectPin, HIGH);
}


void MATRIX7219::clear()
{
  for (uint8_t row = 1; row < 9; row++)
  {
    digitalWrite(_selectPin, LOW);
    for (int m = 0; m < _matrices; m++)
    {
      _write(row);
      _write(0);
    }
    digitalWrite(_selectPin, HIGH);
  }
}


void MATRIX7219::setRow(uint8_t row, uint8_t value, uint8_t matrix)
{
  digitalWrite(_selectPin, LOW);
  for (int m = _matrices; m > matrix; m--)
  {
    _write(0);
    _write(0);
  }

  if (_swap) row = 9 - row;
  _write(row);
  if (_invert)  value = 255 - value;
  if (_reverse) value = _reverse8(value);
  _write(value);

  for (int m = matrix-1; m > 0; m--)
  {
    _write(0);
    _write(0);
  }
  digitalWrite(_selectPin, HIGH);
}


///////////////////////////////////////////////////////
//
//  LAYOUT
//
void MATRIX7219::setInvert(bool invert)
{
  _invert = invert;
}


bool MATRIX7219::getInvert()
{
  return _invert;
}


void MATRIX7219::setReverse(bool rev)
{
  _reverse = rev;
}


bool MATRIX7219::getReverse()
{
  return _reverse;
}


void MATRIX7219::setSwap(bool swap)
{
  _swap = swap;
}


bool MATRIX7219::getSwap()
{
  return _swap;
}


///////////////////////////////////////////////////////
//
//  PRIVATE
//
void MATRIX7219::_write(uint8_t b)
{
  for (uint8_t mask = 0x80; mask > 0; mask >>= 1)
  {
    digitalWrite(_clockPin, LOW);
    digitalWrite(_dataPin, (b & mask) > 0);
    digitalWrite(_clockPin, HIGH);
  }
}


//  optimization not for release 0.1.0
void MATRIX7219::_writeZero()
{
  digitalWrite(_dataPin, LOW);
  for (uint8_t mask = 0x80; mask > 0; mask >>= 1)
  {
    digitalWrite(_clockPin, LOW);
    digitalWrite(_clockPin, HIGH);
  }
}


//  From CRC 0.3.3
uint8_t MATRIX7219::_reverse8(uint8_t in)
{
  uint8_t x = in;
  x = (((x & 0xAA) >> 1) | ((x & 0x55) << 1));
  x = (((x & 0xCC) >> 2) | ((x & 0x33) << 2));
  x =          ((x >> 4) | (x << 4));
  return x;
}

//  -- END OF FILE --

