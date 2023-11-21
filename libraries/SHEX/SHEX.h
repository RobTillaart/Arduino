#pragma once
//
//    FILE: SHEX.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.3
// PURPOSE: Arduino library to generate hex dump over Serial
//    DATE: 2020-05-24
//     URL: https://github.com/RobTillaart/SHEX


#include "Arduino.h"
#include "Print.h"


#define SHEX_LIB_VERSION                (F("0.3.3"))


#if not defined(SHEX_DEFAULT_LENGTH)
#define SHEX_DEFAULT_LENGTH             16
#endif
#if not defined(SHEX_MAX_LENGTH)
#define SHEX_MAX_LENGTH                 32
#endif
#if not defined(SHEX_MIN_LENGTH)
#define SHEX_MIN_LENGTH                 4
#endif
#if not defined(SHEX_COUNTER_DIGITS)
#define SHEX_COUNTER_DIGITS             4
#endif
#if not defined(SHEX_DEFAULT_VTAB)
#define SHEX_DEFAULT_VTAB               8
#endif


class SHEX: public Print
{
public:
  SHEX(Print* stream = &Serial, uint8_t length = SHEX_DEFAULT_LENGTH);

  void     reset();

  size_t   write(uint8_t c);

  void     setHEX(bool hexOutput = true);
  bool     getHEX();

  void     setBytesPerLine(const uint8_t length = SHEX_DEFAULT_LENGTH);
  uint8_t  getBytesPerLine();

  void     setSeparator(char c = ' ');
  char     getSeparator();

  //       must be 0, 4, 6 or 8
  void     setCountDigits(uint8_t digits = SHEX_COUNTER_DIGITS);
  uint8_t  getCountDigits();
  //  restarts the output - use with care
  void     restartOutput();
  uint32_t getCounter();

  void     setVTAB(uint8_t vtab = SHEX_DEFAULT_VTAB);
  uint8_t  getVTAB();


protected:
  Print *   _stream    = &Serial;
  bool      _hexOutput = true;
  uint8_t   _length    = SHEX_DEFAULT_LENGTH;
  uint8_t   _vtab      = SHEX_DEFAULT_VTAB;
  char      _separator = ' ';

  uint32_t  _charCount = 0;
  uint32_t  _digits    = SHEX_COUNTER_DIGITS;
};


///////////////////////////////////////////////////
//
//  SHEXA shows also ASCII dump
//        derived class as it takes extra RAM
//
class SHEXA : public SHEX
{
public:
  SHEXA(Print* stream = &Serial, uint8_t length = SHEX_DEFAULT_LENGTH);

  size_t    write(uint8_t c);
  //  flushes the ASCII column to output;  not ideal but workable for now.
  //  use with care
  void      flushASCII();

protected:
  uint8_t   _txtbuf[SHEX_MAX_LENGTH];
  bool      _showtxt = true;
};


//  -- END OF FILE --

