//
//    FILE: MATRIX7219.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
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

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)
  uint8_t _port    = digitalPinToPort(_dataPin);
  _dataOutRegister = portOutputRegister(_port);
  _dataOutBit      = digitalPinToBitMask(_dataPin);

  _port            = digitalPinToPort(_clockPin);
  _clockRegister   = portOutputRegister(_port);
  _clockBit        = digitalPinToBitMask(_clockPin);
#endif
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
    _writeZero();                       //  No decode for digits 7–0
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
    _writeZero();                       //  normal mode
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
    _writeZero();
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
    else _writeZero();
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
      _writeZero();
    }
    digitalWrite(_selectPin, HIGH);
  }
}


void MATRIX7219::setRow(uint8_t row, uint8_t value, uint8_t matrix)
{
  digitalWrite(_selectPin, LOW);
  for (int m = _matrices; m > matrix; m--)
  {
    _writeZero();
    _writeZero();
  }

  if (_swap) row = 9 - row;
  _write(row);
  if (_invert)  value = 255 - value;
  if (_reverse) value = _reverse8(value);
  _write(value);

  for (int m = matrix - 1; m > 0; m--)
  {
    _writeZero();
    _writeZero();
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
//  PROTECTED
//
void MATRIX7219::_write(uint8_t b)
{
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

  uint8_t cbmask1  = _clockBit;
  uint8_t cbmask2  = ~_clockBit;
  uint8_t outmask1 = _dataOutBit;
  uint8_t outmask2 = ~_dataOutBit;

  for (uint8_t mask = 0x80; mask > 0; mask >>= 1)
  {
    uint8_t oldSREG = SREG;
    noInterrupts();
    if ((b & mask) == 0) *_dataOutRegister &= outmask2;
    else                 *_dataOutRegister |= outmask1;
    *_clockRegister |= cbmask1;
    *_clockRegister &= cbmask2;
    SREG = oldSREG;
  }

#else

  uint8_t clk = _clockPin;
  uint8_t dat = _dataPin;
  for (uint8_t mask = 0x80; mask > 0; mask >>= 1)
  {
    digitalWrite(clk, LOW);
    digitalWrite(dat, (b & mask) > 0);
    digitalWrite(clk, HIGH);
  }

#endif
}


//  optimization
void MATRIX7219::_writeZero()
{
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

  uint8_t cbmask1  = _clockBit;
  uint8_t cbmask2  = ~_clockBit;
  //  uint8_t outmask1 = _dataOutBit;
  uint8_t outmask2 = ~_dataOutBit;

  *_dataOutRegister &= outmask2;

  for (uint8_t mask = 0x80; mask > 0; mask >>= 1)
  {
    uint8_t oldSREG = SREG;
    noInterrupts();
    *_clockRegister |= cbmask1;
    *_clockRegister &= cbmask2;
    SREG = oldSREG;
  }

#else

  uint8_t clk = _clockPin;
  digitalWrite(_dataPin, LOW);
  for (uint8_t mask = 0x80; mask > 0; mask >>= 1)
  {
    digitalWrite(clk, LOW);
    digitalWrite(clk, HIGH);
  }

#endif
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


///////////////////////////////////////////////////////////////
//
//  DERIVED MATRIX7221 CLASS
//
MATRIX7221::MATRIX7221(uint8_t dataPin, uint8_t selectPin, uint8_t clockPin, uint8_t matrices)
          : MATRIX7219(dataPin, selectPin, clockPin, matrices)
          {
          }


//  -- END OF FILE --

