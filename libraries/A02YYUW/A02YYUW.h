#pragma once
//
//    FILE: A02YYUW.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-05-07
// VERSION: 0.1.2
// PURPOSE: Arduino library for A02YYUW serial distance sensor
//     URL: https://github.com/RobTillaart/A02YYUW


#include "Arduino.h"

#define A02YYUW_LIB_VERSION         (F("0.1.2"))

constexpr int A02YY_OK          = 0;
constexpr int A02YY_ERR_CRC     = -100;
constexpr int A02YY_ERR_TIMEOUT = -101;


////////////////////////////////////////////
//
//  BASE CLASS
//
class A02YY
{
public:
  A02YY(Stream * str);

  void     begin();

  //  needed by all
  bool     newDistance();
  uint16_t getDistanceMM();
  float    getDistanceCM();
  float    getDistanceINCH();

  uint32_t lastRead();
  void     flush();

  int      getLastError();

protected:
  Stream * _stream;
  uint8_t  _TX;
  uint8_t  _byte;
  uint8_t  _high, _low;
  uint16_t _millimetres;
  uint32_t _lastRead;
  uint32_t _lastHeader;

  int      _error;
};


////////////////////////////////////////////
//
//  DERIVED CLASSES - UART AUTO - A02YYU(W)
//
class A02YYU : public A02YY
{
  public:
  A02YYU(Stream * str, uint8_t TX) : A02YY(str)
  {
    _TX = TX;
    //  needed? as Serial implies TX == OUTPUT.
    pinMode(_TX, OUTPUT);
  };

  //  true  = processed mode
  //  false = real time mode (default)
  void setProcessingMode(bool mode);
  bool getProcessingMode();
};

//  wrapper only
class A02YYUW : public A02YYU
{
  public:
  A02YYUW(Stream * str, uint8_t TX) : A02YYU(str, TX)
  {
  };
};


////////////////////////////////////////////
//
//  DERIVED CLASSES - UART CONTROLLED - A02YYT(W)
//
class A02YYT : public A02YY
{
  public:
  A02YYT(Stream * str) : A02YY(str)
  {
  };
  void request();
};

//  wrapper only
class A02YYTW : public A02YYT
{
  public:
  A02YYTW(Stream * str) : A02YYT(str)
  {
  };
};


//  -- END OF FILE --





