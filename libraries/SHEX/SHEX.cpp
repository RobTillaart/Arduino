//
//    FILE: SHEX.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: Arduino library to generate hex dump over Serial
//    DATE: 2020-05-24
//     URL: https://github.com/RobTillaart/SHEX
//
//  HISTORY:
//  0.1.0   2020-05-24  initial version
//  0.1.1   2020-06-19  fix library.json
//  0.2.0   2021-01-07  Arduino-CI + unit tests + modifiers.
//  0.2.1   2021-12-28  update library.json, readme, license, minor edits


#include "SHEX.h"


SHEX::SHEX(Print* stream, uint8_t length)
{
  _stream  = stream;
  reset();
  // force multiple of 4; max 32
  _length = ((length + 3) / 4) * 4;
  if (_length > 32) _length = 32;
};


void SHEX::reset()
{
  _hexOutput = false;
  _length    = 0;
  _charCount = 0;
  _separator = ' ';
  _countFlag = true;
}


///////////////////////////////////////////
//
// WRITE - the core
//
size_t SHEX::write(uint8_t c)
{
  // PASS THROUGH MODE
  if (_hexOutput == false) return _stream->write(c);

  // HEX MODE
  // handle end of line and position number
  if ((_charCount % _length) == 0)
  {
    _stream->println();
    // separator line every 8 lines
    if ((_charCount % (_length * 8)) == 0)
    {
      _stream->println();
    }

    // next line
    if (_countFlag)
    {
      uint32_t mask = 0xF0000000;
      while((mask > 0xF) && (mask & _charCount) == 0)
      {
        _stream->print('0');
        mask >>= 4;
      }
      _stream->print(_charCount, HEX);
      _stream->print('\t');
    }
  }

  // Print char as HEX
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
  _charCount = 0;
  _stream->println();
};


void SHEX::setBytesPerLine(const uint8_t length)
{
  // force multiple of 4; max 32
  _length = ((length + 3) / 4) * 4;
  if (_length > 32) _length = 32;
  _charCount = 0;
  _stream->println();
}


// -- END OF FILE --

