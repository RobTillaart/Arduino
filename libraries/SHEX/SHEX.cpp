//
//    FILE: SHEX.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.3
// PURPOSE: Arduino library to generate hex dump over Serial
//    DATE: 2020-05-24
//     URL: https://github.com/RobTillaart/SHEX


#include "SHEX.h"


SHEX::SHEX(Print* stream, uint8_t length)
{
  _stream  = stream;
  reset();
  //  force multiple of 4;  max 32
  _length = ((length + 3) / 4) * 4;
  if (_length > SHEX_MAX_LENGTH)
  {
    _length = SHEX_MAX_LENGTH;
  }
  if (_length < SHEX_MIN_LENGTH)
  {
    _length = SHEX_MIN_LENGTH;
  }
}


void SHEX::reset()
{
  _hexOutput = true;
  _length    = SHEX_DEFAULT_LENGTH;
  _charCount = 0;
  _separator = ' ';
  _digits    = SHEX_COUNTER_DIGITS;
  _vtab      = SHEX_DEFAULT_VTAB;
}


///////////////////////////////////////////
//
//  WRITE - the core
//
size_t SHEX::write(uint8_t c)
{
  //  PASS THROUGH MODE
  if (_hexOutput == false) return _stream->write(c);

  //  HEX MODE
  //  handle end of line and position number
  if ((_charCount % _length) == 0)
  {
    //  insert ASCII array here

    _stream->println();
    //  separator line every _vtab (default 8) lines
    if ((_charCount % (_length * _vtab)) == 0)
    {
      _stream->println();
    }

    //  next line
    if (_digits > 0)
    {
      uint32_t mask = 0xF000;
      if (_digits > 4) mask = 0xF00000;
      if (_digits > 6) mask = 0xF0000000;
      while((mask > 0xF) && (mask & _charCount) == 0)
      {
        _stream->print('0');
        mask >>= 4;
      }
      _stream->print(_charCount, HEX);
      _stream->print('\t');
    }
  }

  //  Print char as HEX
  if (c < 0x10) _stream->print('0');
  _stream->print(c, HEX);
  _stream->print(_separator);
  _charCount++;
  if ((_charCount % 4) == 0) _stream->print(_separator);

  return 1;
}


void SHEX::setHEX(bool hexOutput)
{
  _hexOutput = hexOutput;
  restartOutput();
}


bool SHEX::getHEX()
{
  return _hexOutput;
}


void SHEX::setBytesPerLine(const uint8_t length)
{
  //  force multiple of 4; max 32
  _length = ((length + 3) / 4) * 4;
  if (_length > SHEX_MAX_LENGTH)
  {
    _length = SHEX_MAX_LENGTH;
  }
  if (_length < SHEX_MIN_LENGTH)
  {
    _length = SHEX_MIN_LENGTH;
  }
  restartOutput();
}


uint8_t SHEX::getBytesPerLine()
{
  return _length;
}


void SHEX::setSeparator(char c)
{
  _separator = c;
}


char SHEX::getSeparator()
{
  return _separator;
}


uint8_t SHEX::getCountDigits()
{
  return _digits;
}


uint32_t SHEX::getCounter()
{
  return _charCount;
}


void SHEX::setVTAB(uint8_t vtab)
{
  _vtab = vtab;
  restartOutput();
};


uint8_t SHEX::getVTAB()
{
  return _vtab;
}


void SHEX::setCountDigits(uint8_t digits)
{
  _digits = digits;
  if (_digits == 0) return;
  if (_digits < 4) _digits = 4;
  if (_digits > 8) _digits = 8;
  restartOutput();
};


void SHEX::restartOutput()
{
  //  prevent change in middle of line
  _charCount = 0;
  _stream->println();
}


///////////////////////////////////////////////////
//
//  SHEXA
//
SHEXA::SHEXA(Print* stream, uint8_t length) : SHEX(stream, length)
{
}


size_t SHEXA::write(uint8_t c)
{
  //  PASS THROUGH MODE
  if (_hexOutput == false) return _stream->write(c);

  //  HEX MODE
  //  handle end of line and position number
  if ((_charCount % _length) == 0)
  {
    //  printable ASCII column
    if (_charCount != 0) 
    {
      flushASCII();
    }

    _stream->println();
    //  separator line every _vtab (default 8) lines
    if ((_charCount % (_length * _vtab)) == 0)
    {
      _stream->println();
    }

    //  next line
    if (_digits > 0)
    {
      uint32_t mask = 0xF000;
      if (_digits > 4) mask = 0xF00000;
      if (_digits > 6) mask = 0xF0000000;
      while((mask > 0xF) && (mask & _charCount) == 0)
      {
        _stream->print('0');
        mask >>= 4;
      }
      _stream->print(_charCount, HEX);
      _stream->print('\t');
    }
  }

  //  Print char as HEX
  if (c < 0x10) _stream->print('0');
  _stream->print(c, HEX);
  _stream->print(_separator);

  //  Store in _txtbuf
  _txtbuf[_charCount % _length] = isPrintable(c) ? c : '.';

  _charCount++;
  if ((_charCount % 4) == 0) _stream->print(_separator);

  return 1;
}


void SHEXA::flushASCII()
{
  uint8_t len = _charCount % _length;
  if (len == 0)
  {
    len = _length;
  }
  if (len < _length)
  {
    for (uint8_t i = len; i < _length; i++)
    {
      _stream->print("   ");
    }
    for (uint8_t i = 0; i < (_length/4 - len/4); i++)
    {
      _stream->print(" ");
    }
  }

  for (uint8_t i = 0; i < len;)
  {
    _stream->write(_txtbuf[i++]);
    if ((i % 8) == 0)
    {
      _stream->print("  ");
    }
  }
}


//  -- END OF FILE --

